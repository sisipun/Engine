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
            Matrix<D, D, T> result;
            for (size_t i = 0; i < D; i++)
            {
                result.data[i * D + i] = 1;
            }
            return result;
        }

        template <size_t D, typename T>
        Matrix<D, D, T> inverse(const Matrix<D, D, T> &matrix)
        {
            Matrix<D, D, T> result;
            for (size_t i = 0; i < D; i++)
            {
                for (size_t j = 0; j < D; j++)
                {
                    result.data[j * D + i] = pow(-1, i + j) * determinant(excludeRowAndColumn(matrix, i, j));
                }
            }
            return result * (1 / determinant(matrix));
        }

        template <size_t D, typename T>
        typename std::enable_if<(D > 1), T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            T result = 0;
            for (size_t i = 0; i < D; i++)
            {
                result += pow(-1, i) * matrix.data[i] * determinant(excludeRowAndColumn(matrix, 0, i));
            }
            return result;
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
            Matrix<D - 1, D - 1, T> result;
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
                    result.data[(i < rowIndex ? i : i - 1) * (D - 1) + (j < columnIndex ? j : j - 1)] = matrix.data[i * D + j];
                }
            }
            return result;
        }
    }
}

#endif