#ifndef PICKLE_MATH_MATRIX_OPERATIONS
#define PICKLE_MATH_MATRIX_OPERATIONS

#include <cmath>

#include "matrix.h"

namespace pickle
{
    namespace math
    {
        template <int D, typename T>
        Matrix<D, D, T> identity()
        {
            Matrix<D, D, T> identityMatrix;
            for (int i = 0; i < D; i++)
            {
                identityMatrix.data[i * D + i] = 1;
            }
            return identityMatrix;
        }

        template <int R, int C, typename T>
        Matrix<C, R, T> transpose(const Matrix<R, C, T> &matrix)
        {
            Matrix<C, R, T> transposed;
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    int index = i * C + j;
                    transposed.data[j * R + i] = matrix.data[i * C + j];
                }
            }
            return transposed;
        }

        template <int D, typename T>
        Matrix<D, D, T> inverse(const Matrix<D, D, T> &matrix)
        {
            Matrix<D, D, T> inverse;
            for (int i = 0; i < D; i++)
            {
                for (int j = 0; j < D; j++)
                {
                    Matrix<D - 1, D - 1, T> subMatrix;
                    for (int k = 0; k < D; k++)
                    {
                        if (k == i)
                        {
                            continue;
                        }
                        for (int l = 0; l < D; l++)
                        {
                            if (l == j)
                            {
                                continue;
                            }
                            subMatrix.data[(k < i ? k : k - 1) * (D - 1) + (l < j ? l : l - 1)] = matrix.data[k * D + l];
                        }
                    }
                    inverse.data[j * D + i] = pow(-1, i + j) * determinant(subMatrix);
                }
            }
            return inverse * (1 / determinant(matrix));
        }

        template <int D, typename T>
        typename std::enable_if<(D > 1), T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            T value = 0;
            for (int i = 0; i < D; i++)
            {
                Matrix<D - 1, D - 1, T> subMatrix;
                for (int j = 1; j < D; j++)
                {
                    for (int k = 0; k < D; k++)
                    {
                        if (k == i)
                        {
                            continue;
                        }
                        subMatrix.data[(j - 1) * (D - 1) + (k < i ? k : k - 1)] = matrix.data[j * D + k];
                    }
                }
                value += pow(-1, i) * matrix.data[i] * determinant(subMatrix);
            }
            return value;
        }

        template <int D, typename T>
        typename std::enable_if<D == 0, T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            return 0;
        }

        template <int D, typename T>
        typename std::enable_if<D == 1, T>::type determinant(const Matrix<D, D, T> &matrix)
        {
            return matrix.data[0];
        }
    }
}

#endif