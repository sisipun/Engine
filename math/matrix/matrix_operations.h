#ifndef PICKLE_MATH_MATRIX_OPERATIONS
#define PICKLE_MATH_MATRIX_OPERATIONS

#include <cmath>

#include "matrix.h"

namespace pickle
{
    namespace math
    {
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
        Matrix<D, D, T> identity()
        {
            Matrix<D, D, T> identityMatrix;
            for (int i = 0; i < D; i++)
            {
                identityMatrix.data[i * D + i] = 1;
            }
            return identityMatrix;
        }

        template <int D>
        float determinant(const Matrix<D, D, float> &matrix)
        {
            float value = 0;
            for (int i = 0; i < D; i++)
            {
                Matrix<D - 1, D - 1, float> subMatrix;
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

        template <>
        float determinant<0>(const Matrix<0, 0, float> &matrix)
        {
            return 0;
        }

        template <>
        float determinant<1>(const Matrix<1, 1, float> &matrix)
        {
            return matrix.data[0];
        }
    }
}

#endif