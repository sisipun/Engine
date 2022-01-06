#ifndef PICKLE_MATH_MATRIX_OPERATIONS
#define PICKLE_MATH_MATRIX_OPERATIONS

#include <cmath>

#include "matrix.h"

namespace pickle
{
    namespace math
    {
        template <size_t D, typename T>
        Matrix<D, D, T> identity()
        {
            Matrix<D, D, T> identityMatrix;
            for (size_t i = 0; i < D; i++)
            {
                identityMatrix.data[i * D + i] = 1;
            }
            return identityMatrix;
        }

        template <size_t R, size_t C, typename T>
        Matrix<C, R, T> transpose(const Matrix<R, C, T> &matrix)
        {
            Matrix<C, R, T> transposed;
            for (size_t i = 0; i < R; i++)
            {
                for (size_t j = 0; j < C; j++)
                {
                    size_t index = i * C + j;
                    transposed.data[j * R + i] = matrix.data[i * C + j];
                }
            }
            return transposed;
        }

        template <size_t D, typename T>
        Matrix<D, D, T> inverse(const Matrix<D, D, T> &matrix)
        {
            Matrix<D, D, T> inverse;
            for (size_t i = 0; i < D; i++)
            {
                for (size_t j = 0; j < D; j++)
                {
                    inverse.data[j * D + i] = pow(-1, i + j) * determinant(excludeRowAndColumn(matrix, i, j));
                }
            }
            return inverse * (1 / determinant(matrix));
        }

        template <size_t D, typename T>
        typename std::enable_if<(D > 1), T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            T value = 0;
            for (size_t i = 0; i < D; i++)
            {
                value += pow(-1, i) * matrix.data[i] * determinant(excludeRowAndColumn(matrix, 0, i));
            }
            return value;
        }

        template <size_t D, typename T>
        typename std::enable_if<D == 0, T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            return 0;
        }

        template <size_t D, typename T>
        typename std::enable_if<D == 1, T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            return matrix.data[0];
        }

        template <size_t D, typename T>
        Matrix<D - 1, D - 1, T> excludeRowAndColumn(const Matrix<D, D, T> &matrix, size_t rowIndex, size_t columnIndex)
        {
            Matrix<D - 1, D - 1, T> excludedMatrix;
            for (size_t i = 0; i < D; i++)
            {
                if (i == rowIndex)
                {
                    continue;
                }
                for (size_t j = 0; j < D; j++)
                {
                    if (j == columnIndex)
                    {
                        continue;
                    }
                    excludedMatrix.data[(i < rowIndex ? i : i - 1) * (D - 1) + (j < columnIndex ? j : j - 1)] = matrix.data[i * D + j];
                }
            }
            return excludedMatrix;
        }
    }
}

#endif