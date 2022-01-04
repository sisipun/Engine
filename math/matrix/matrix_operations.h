#ifndef PICKLE_MATH_MATRIX_OPERATIONS
#define PICKLE_MATH_MATRIX_OPERATIONS

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
    }
}

#endif