#ifndef PICKLE_MATH_MATRIX
#define PICKLE_MATH_MATRIX

namespace pickle
{
    namespace math
    {
        template <size_t ROWS, size_t COLUMNS, typename T>
        class Matrix
        {
        public:
            Matrix() : data{0}
            {
            }

            Matrix(const T (&data)[ROWS * COLUMNS])
            {
                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        size_t index = i * COLUMNS + j;
                        this->data[index] = data[index];
                    }
                }
            }

            Matrix(const Matrix<ROWS, COLUMNS, T> &matrix) : Matrix(matrix.data)
            {
            }

            ~Matrix() = default;

            Matrix<ROWS, COLUMNS, T> &operator=(const Matrix<ROWS, COLUMNS, T> &matrix)
            {
                if (this == &matrix)
                {
                    return *this;
                }

                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        size_t index = i * COLUMNS + j;
                        this->data[index] = matrix.data[index];
                    }
                }
                return *this;
            }

            Matrix<ROWS, COLUMNS, T> operator+(const Matrix<ROWS, COLUMNS, T> &matrix) const
            {
                Matrix<ROWS, COLUMNS, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        size_t index = i * COLUMNS + j;
                        result.data[index] = data[index] + matrix.data[index];
                    }
                }
                return result;
            }

            Matrix<ROWS, COLUMNS, T> operator-(const Matrix<ROWS, COLUMNS, T> &matrix) const
            {
                Matrix<ROWS, COLUMNS, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        size_t index = i * COLUMNS + j;
                        result.data[index] = data[index] - matrix.data[index];
                    }
                }
                return result;
            }

            Matrix<ROWS, COLUMNS, T> operator*(float scalar) const
            {
                Matrix<ROWS, COLUMNS, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        size_t index = i * COLUMNS + j;
                        result.data[index] = data[index] * scalar;
                    }
                }
                return result;
            }

            template <size_t NEW_COLUMNS>
            Matrix<ROWS, NEW_COLUMNS, T> operator*(const Matrix<COLUMNS, NEW_COLUMNS, T> &matrix) const
            {
                Matrix<ROWS, NEW_COLUMNS, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < NEW_COLUMNS; j++)
                    {
                        T value = 0;
                        for (size_t k = 0; k < COLUMNS; k++)
                        {
                            value += data[i * COLUMNS + k] * matrix.data[k * NEW_COLUMNS + j];
                        }
                        result.data[i * NEW_COLUMNS + j] = value;
                    }
                }
                return result;
            }

            Vector<ROWS, T> operator*(const Vector<COLUMNS, T> &vector) const
            {
                Vector<ROWS, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    T value = 0;
                    for (size_t k = 0; k < COLUMNS; k++)
                    {
                        value += data[i * COLUMNS + k] * vector.data[k];
                    }
                    result.data[i] = value;
                }
                return result;
            }

            Matrix<ROWS, COLUMNS, T> operator/(float divider) const
            {
                Matrix<ROWS, COLUMNS, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        size_t index = i * COLUMNS + j;
                        result.data[index] = data[index] / divider;
                    }
                }
                return result;
            }

            template <size_t ROW_POSITION>
            typename std::enable_if<(ROW_POSITION < ROWS), Matrix<ROWS - 1, COLUMNS, T>>::type cutRowDimension() const
            {
                return cutRowDimension<ROW_POSITION, 1>();
            }

            template <size_t COLUMN_POSITION>
            typename std::enable_if<(COLUMN_POSITION <= COLUMNS), Matrix<ROWS, COLUMNS - 1, T>>::type cutColumnDimension() const
            {
                return cutColumnDimension<COLUMN_POSITION, 1>();
            }

            template <size_t ROW_POSITION, size_t ROWS_COUNT>
            typename std::enable_if<ROW_POSITION + ROWS_COUNT <= ROWS, Matrix<ROWS - ROWS_COUNT, COLUMNS, T>>::type cutRowDimension() const
            {
                return cutDimension<ROW_POSITION, ROWS_COUNT, 0, 0>();
            }

            template <size_t COLUMN_POSITION, size_t COLUMNS_COUNT>
            typename std::enable_if<COLUMN_POSITION + COLUMNS_COUNT <= COLUMNS, Matrix<ROWS, COLUMNS - COLUMNS_COUNT, T>>::type cutColumnDimension() const
            {
                return cutDimension<0, 0, COLUMN_POSITION, COLUMNS_COUNT>();
            }

            template <size_t ROW_POSITION, size_t COLUMN_POSITION>
            typename std::enable_if<(ROW_POSITION < ROWS) && (COLUMN_POSITION < COLUMNS), Matrix<ROWS - 1, COLUMNS - 1, T>>::type cutDimension() const
            {
                return cutDimension<ROW_POSITION, 1, COLUMN_POSITION, 1>();
            }

            template <size_t ROW_POSITION, size_t ROWS_COUNT, size_t COLUMN_POSITION, size_t COLUMNS_COUNT>
            typename std::enable_if<ROW_POSITION + ROWS_COUNT <= ROWS && COLUMN_POSITION + COLUMNS_COUNT <= COLUMNS, Matrix<ROWS - ROWS_COUNT, COLUMNS - COLUMNS_COUNT, T>>::type cutDimension() const
            {
                Matrix<ROWS - ROWS_COUNT, COLUMNS - COLUMNS_COUNT, T> result;
                for (size_t i = 0, ri = 0; i < ROWS; i++)
                {
                    if (i < ROW_POSITION || i >= ROW_POSITION + ROWS_COUNT)
                    {
                        for (size_t j = 0, rj = 0; j < COLUMNS; j++)
                        {
                            if (j < COLUMN_POSITION || j >= COLUMN_POSITION + COLUMNS_COUNT)
                            {
                                result.data[ri * (COLUMNS - COLUMNS_COUNT) + rj] = data[i * COLUMNS + j];
                                rj++;
                            }
                        }
                        ri++;
                    }
                }
                return result;
            }

            template <size_t ROW_POSITION, size_t ROWS_COUNT, size_t COLUMN_POSITION, size_t COLUMNS_COUNT>
            typename std::enable_if<(ROWS_COUNT > 0) && ROW_POSITION + ROWS_COUNT <= ROWS && (COLUMNS_COUNT > 0) && COLUMN_POSITION + COLUMNS_COUNT <= COLUMNS, Matrix<ROWS_COUNT, COLUMNS_COUNT, T>>::type extract() const
            {
                Matrix<ROWS_COUNT, COLUMNS_COUNT, T> result;
                for (size_t i = 0, ri = 0; i < ROWS; i++)
                {
                    if (i >= ROW_POSITION && i < ROW_POSITION + ROWS_COUNT)
                    {
                        for (size_t j = 0, rj = 0; j < COLUMNS; j++)
                        {
                            if (j >= COLUMN_POSITION && j < COLUMN_POSITION + COLUMNS_COUNT)
                            {
                                result.data[ri * (COLUMNS_COUNT) + rj] = data[i * COLUMNS + j];
                                rj++;
                            }
                        }
                        ri++;
                    }
                }
                return result;
            }

            template <size_t ROW_POSITION>
            typename std::enable_if<(ROW_POSITION < ROWS), Matrix<ROWS + 1, COLUMNS, T>>::type addRowDimension(Matrix<1, COLUMNS, T> value) const
            {
                return addRowDimension<ROW_POSITION, 1>(value);
            }

            template <size_t ROW_POSITION, size_t ROWS_COUNT>
            typename std::enable_if<(ROW_POSITION < ROWS), Matrix<ROWS + ROWS_COUNT, COLUMNS, T>>::type addRowDimension(Matrix<ROWS_COUNT, COLUMNS, T> value) const
            {
                Matrix<ROWS + ROWS_COUNT, COLUMNS, T> result;
                size_t ri = 0;
                for (size_t i = 0; i < ROW_POSITION; i++, ri++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        result.data[ri * COLUMNS + j] = data[i * COLUMNS + j];
                    }
                }

                for (size_t i = 0; i < ROWS_COUNT; i++, ri++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        result.data[ri * COLUMNS + j] = value.data[i * COLUMNS + j];
                    }
                }

                for (size_t i = ROW_POSITION; i < ROWS; i++, ri++)
                {
                    for (size_t j = 0; j < COLUMNS; j++)
                    {
                        result.data[ri * COLUMNS + j] = data[i * COLUMNS + j];
                    }
                }
                return result;
            }

            template <size_t COLUMN_POSITION>
            typename std::enable_if<(COLUMN_POSITION < COLUMNS), Matrix<ROWS, COLUMNS + 1, T>>::type addColumnDimension(Matrix<ROWS, 1, T> value) const
            {
                return addColumnDimension<COLUMN_POSITION, 1>(value);
            }

            template <size_t COLUMN_POSITION, size_t COLUMNS_COUNT>
            typename std::enable_if<(COLUMN_POSITION < COLUMNS), Matrix<ROWS, COLUMNS + COLUMNS_COUNT, T>>::type addColumnDimension(Matrix<ROWS, COLUMNS_COUNT, T> value) const
            {
                Matrix<ROWS, COLUMNS + COLUMNS_COUNT, T> result;
                for (size_t i = 0; i < ROWS; i++)
                {
                    size_t rj = 0;
                    for (size_t j = 0; j < COLUMN_POSITION; j++, rj++)
                    {
                        result.data[i * (COLUMNS + COLUMNS_COUNT) + rj] = data[i * COLUMNS + j];
                    }

                    for (size_t j = 0; j < COLUMNS_COUNT; j++, rj++)
                    {
                        result.data[i * (COLUMNS + COLUMNS_COUNT) + rj] = value.data[i * COLUMNS_COUNT + j];
                    }

                    for (size_t j = COLUMN_POSITION; j < COLUMNS; j++, rj++)
                    {
                        result.data[i * (COLUMNS + COLUMNS_COUNT) + rj] = data[i * COLUMNS + j];
                    }
                }
                return result;
            }

            template <size_t ROW_POSITION, size_t COLUMNS_COUNT>
            typename std::enable_if<(ROW_POSITION < ROWS) && (COLUMNS_COUNT < COLUMNS), Matrix<ROWS, COLUMNS, T>>::type replace(T value) const
            {
                return replace<ROW_POSITION, 1, COLUMNS_COUNT, 1>(Matrix<1, 1, T>({value}));
            }

            template <size_t ROW_POSITION, size_t ROWS_COUNT, size_t COLUMN_POSITION, size_t COLUMNS_COUNT>
            typename std::enable_if<(ROWS_COUNT > 0) && ROW_POSITION + ROWS_COUNT <= ROWS && (COLUMNS_COUNT > 0) && COLUMN_POSITION + COLUMNS_COUNT <= COLUMNS, Matrix<ROWS, COLUMNS, T>>::type replace(Matrix<ROWS_COUNT, COLUMNS_COUNT, T> value) const
            {
                Matrix<ROWS, COLUMNS, T> result(data);
                for (size_t i = 0; i < ROWS_COUNT; i++)
                {
                    for (size_t j = 0; j < COLUMNS_COUNT; j++)
                    {
                        result.data[(i + ROW_POSITION) * COLUMNS + (j + COLUMN_POSITION)] = value.data[i * COLUMNS_COUNT + j];
                    }
                }
                return result;
            }

            size_t rows() const
            {
                return ROWS;
            }

            size_t columns() const
            {
                return COLUMNS;
            }

        public:
            T data[ROWS * COLUMNS];
        };
    }
}

#endif