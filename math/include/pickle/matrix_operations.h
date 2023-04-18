#ifndef PICKLE_MATH_MATRIX_OPERATIONS
#define PICKLE_MATH_MATRIX_OPERATIONS

#include <cmath>

#include "matrix.h"
#include "quaternion.h"

namespace pickle
{
    namespace math
    {
        template <size_t SIZE, typename TYPE>
        Matrix<SIZE, SIZE, TYPE> identity()
        {
            Matrix<SIZE, SIZE, TYPE> result;
            for (size_t i = 0; i < SIZE; i++)
            {
                result.data[i * SIZE + i] = 1;
            }
            return result;
        }

        template <size_t SIZE, typename TYPE>
        Matrix<SIZE, SIZE, TYPE> inverse(const Matrix<SIZE, SIZE, TYPE> &matrix)
        {
            Matrix<SIZE, SIZE, TYPE> result;
            for (size_t i = 0; i < SIZE; i++)
            {
                for (size_t j = 0; j < SIZE; j++)
                {
                    result.data[j * SIZE + i] = TYPE(pow(-1, i + j)) * determinant(excludeRowAndColumn(matrix, i, j));
                }
            }
            return result * (1 / determinant(matrix));
        }

        template <size_t ROWS, size_t COLUMNS, typename TYPE>
        Matrix<COLUMNS, ROWS, TYPE> transpose(const Matrix<ROWS, COLUMNS, TYPE> &matrix)
        {
            Matrix<COLUMNS, ROWS, TYPE> result;
            for (size_t i = 0; i < ROWS; i++)
            {
                for (size_t j = 0; j < COLUMNS; j++)
                {
                    size_t index = i * COLUMNS + j;
                    result.data[j * ROWS + i] = matrix.data[i * COLUMNS + j];
                }
            }
            return result;
        }

        template <size_t SIZE, typename TYPE>
        typename std::enable_if<(SIZE > 1), TYPE>::type determinant(const Matrix<SIZE, SIZE, TYPE> &matrix)
        {
            TYPE result = 0;
            for (size_t i = 0; i < SIZE; i++)
            {
                result += TYPE(pow(-1, i)) * matrix.data[i] * determinant(excludeRowAndColumn(matrix, 0, i));
            }
            return result;
        }

        template <size_t SIZE, typename TYPE>
        typename std::enable_if<SIZE == 0, TYPE>::type determinant(const Matrix<SIZE, SIZE, TYPE> &matrix)
        {
            return 0;
        }

        template <size_t SIZE, typename TYPE>
        typename std::enable_if<SIZE == 1, TYPE>::type determinant(const Matrix<SIZE, SIZE, TYPE> &matrix)
        {
            return matrix.data[0];
        }

        template <size_t SIZE, typename TYPE>
        Matrix<SIZE - 1, SIZE - 1, TYPE> excludeRowAndColumn(const Matrix<SIZE, SIZE, TYPE> &matrix, size_t rowIndex, size_t columnIndex)
        {
            Matrix<SIZE - 1, SIZE - 1, TYPE> result;
            for (size_t i = 0; i < SIZE; i++)
            {
                if (i == rowIndex)
                {
                    continue;
                }
                for (size_t j = 0; j < SIZE; j++)
                {
                    if (j == columnIndex)
                    {
                        continue;
                    }
                    result.data[(i < rowIndex ? i : i - 1) * (SIZE - 1) + (j < columnIndex ? j : j - 1)] = matrix.data[i * SIZE + j];
                }
            }
            return result;
        }

        template <typename TYPE>
        Quaternion<TYPE> toQuaternion(const Matrix<3, 3, TYPE> &matrix)
        {
            TYPE trace = matrix.data[0] + matrix.data[4] + matrix.data[8];
            if (trace > 0)
            {
                TYPE s = 0.5f / TYPE(sqrt(trace + 1.0f));
                return Quaternion<TYPE>(
                    0.25f / s,
                    (matrix.data[7] - matrix.data[5]) * s,
                    (matrix.data[2] - matrix.data[6]) * s,
                    (matrix.data[3] - matrix.data[1]) * s);
            }

            if (matrix.data[0] > matrix.data[4] && matrix.data[0] > matrix.data[8])
            {
                float s = 2.0f * TYPE(sqrt(1.0f + matrix.data[0] - matrix.data[4] - matrix.data[8]));
                return Quaternion<TYPE>(
                    (matrix.data[7] - matrix.data[5]) / s,
                    0.25f * s,
                    (matrix.data[1] + matrix.data[3]) / s,
                    (matrix.data[2] + matrix.data[6]) / s);
            }
            else if (matrix.data[4] > matrix.data[8])
            {
                float s = 2.0f * sqrtf(1.0f + matrix.data[4] - matrix.data[0] - matrix.data[8]);
                return Quaternion<TYPE>(
                    (matrix.data[2] - matrix.data[6]) / s,
                    (matrix.data[1] + matrix.data[3]) / s,
                    0.25f * s,
                    (matrix.data[5] + matrix.data[7]) / s);
            }
            else
            {
                float s = 2.0f * sqrtf(1.0f + matrix.data[8] - matrix.data[0] - matrix.data[4]);
                return Quaternion<TYPE>(
                    (matrix.data[3] - matrix.data[1]) / s,
                    (matrix.data[2] + matrix.data[6]) / s,
                    (matrix.data[5] + matrix.data[7]) / s,
                    0.25f * s);
            }
        }

        template <typename TYPE>
        Quaternion<TYPE> toQuaternion(const Matrix<4, 4, TYPE> &matrix)
        {
            return toQuaternion(matrix.cutColumnDimension<3, 3>());
        }
    }
}

#endif