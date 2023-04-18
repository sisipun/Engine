#ifndef PICKLE_MATH_MATRIX_OPERATIONS
#define PICKLE_MATH_MATRIX_OPERATIONS

#include <cmath>

#include "matrix.h"

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
    }
}

#endif