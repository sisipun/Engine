#ifndef PICKLE_MATH_MATRIX
#define PICKLE_MATH_MATRIX

namespace pickle
{
    namespace math
    {
        template <size_t R, size_t C, typename T>
        class Matrix
        {
        public:
            Matrix() : data{0}
            {
            }

            Matrix(const T (&data)[R * C])
            {
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        this->data[index] = data[index];
                    }
                }
            }

            Matrix(const Matrix<R, C, T> &matrix) : Matrix(matrix.data)
            {
            }

            ~Matrix() = default;

            Matrix<R, C, T> &operator=(const Matrix<R, C, T> &matrix)
            {
                if (this == &matrix)
                {
                    return *this;
                }

                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        this->data[index] = matrix.data[index];
                    }
                }
                return *this;
            }

            Matrix<R, C, T> operator+(const Matrix<R, C, T> &matrix) const
            {
                Matrix<R, C, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        result.data[index] = data[index] + matrix.data[index];
                    }
                }
                return result;
            }

            Matrix<R, C, T> operator-(const Matrix<R, C, T> &matrix) const
            {
                Matrix<R, C, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        result.data[index] = data[index] - matrix.data[index];
                    }
                }
                return result;
            }

            Matrix<R, C, T> operator*(float scalar) const
            {
                Matrix<R, C, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        result.data[index] = data[index] * scalar;
                    }
                }
                return result;
            }

            template <size_t NC>
            Matrix<R, NC, T> operator*(const Matrix<C, NC, T> &matrix) const
            {
                Matrix<R, NC, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < NC; j++)
                    {
                        T value = 0;
                        for (size_t k = 0; k < C; k++)
                        {
                            value += data[i * C + k] * matrix.data[k * NC + j];
                        }
                        result.data[i * NC + j] = value;
                    }
                }
                return result;
            }

            Vector<R, T> operator*(const Vector<C, T> &vector) const
            {
                Vector<R, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    T value = 0;
                    for (size_t k = 0; k < C; k++)
                    {
                        value += data[i * C + k] * vector.data[k];
                    }
                    result.data[i] = value;
                }
                return result;
            }

            Matrix<R, C, T> operator/(float divider) const
            {
                Matrix<R, C, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        result.data[index] = data[index] / divider;
                    }
                }
                return result;
            }

            Matrix<C, R, T> transpose()
            {
                Matrix<C, R, T> result;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        result.data[j * R + i] = data[i * C + j];
                    }
                }
                return result;
            }

            template <size_t RP>
            typename std::enable_if<(RP < R), Matrix<R - 1, C, T>>::type cutRowDimension()
            {
                return cutRowDimension<RP, 1>();
            }

            template <size_t CP>
            typename std::enable_if<(CP <= C), Matrix<R, C - 1, T>>::type cutColumnDimension()
            {
                return cutColumnDimension<CP, 1>();
            }

            template <size_t RP, size_t RC>
            typename std::enable_if<RP + RC <= R, Matrix<R - RC, C, T>>::type cutRowDimension()
            {
                return cutDimension<RP, RC, 0, 0>();
            }

            template <size_t CP, size_t CC>
            typename std::enable_if<CP + CC <= C, Matrix<R, C - CC, T>>::type cutColumnDimension()
            {
                return cutDimension<0, 0, CP, CC>();
            }

            template <size_t RP, size_t CP>
            typename std::enable_if<(RP < R) && (CP < C), Matrix<R - 1, C - 1, T>>::type cutDimension()
            {
                return cutDimension<RP, 1, CP, 1>();
            }

            template <size_t RP, size_t RC, size_t CP, size_t CC>
            typename std::enable_if<RP + RC <= R && CP + CC <= C, Matrix<R - RC, C - CC, T>>::type cutDimension()
            {
                Matrix<R - RC, C - CC, T> result;
                for (size_t i = 0, ri = 0; i < R; i++)
                {
                    if (i < RP || i >= RP + RC)
                    {
                        for (size_t j = 0, rj = 0; j < C; j++)
                        {
                            if (j < CP || j >= CP + CC)
                            {
                                result.data[ri * (C - CC) + rj] = data[i * C + j];
                                rj++;
                            }
                        }
                        ri++;
                    }
                }
                return result;
            }

            template <size_t RP, size_t RC, size_t CP, size_t CC>
            typename std::enable_if<(RC > 0) && RP + RC <= R && (CC > 0) && CP + CC <= C, Matrix<RC, CC, T>>::type extract()
            {
                Matrix<RC, CC, T> result;
                for (size_t i = 0, ri = 0; i < R; i++)
                {
                    if (i >= RP && i < RP + RC)
                    {
                        for (size_t j = 0, rj = 0; j < C; j++)
                        {
                            if (j >= CP && j < CP + CC)
                            {
                                result.data[ri * (CC) + rj] = data[i * C + j];
                                rj++;
                            }
                        }
                        ri++;
                    }
                }
                return result;
            }

            template <size_t RP, size_t CC>
            typename std::enable_if<(RP < R) && (CC < C), Matrix<R, C, T>>::type replace(T value)
            {
                return replace<RP, 1, CC, 1>(Matrix<1, 1, T>({value}));
            }

            template <size_t RP, size_t RC, size_t CP, size_t CC>
            typename std::enable_if<(RC > 0) && RP + RC <= R && (CC > 0) && CP + CC <= C, Matrix<R, C, T>>::type replace(Matrix<RC, CC, T> value)
            {
                Matrix<R, C, T> result(data);
                for (size_t i = 0; i < RC; i++)
                {
                    for (size_t j = 0; j < CC; j++)
                    {
                        result.data[(i + RP) * C + (j + CP)] = value.data[i * CC + j];
                    }
                }
                return result;
            }

            size_t rows() const
            {
                return R;
            }

            size_t columns() const
            {
                return C;
            }

        public:
            T data[R * C];
        };
    }
}

#endif