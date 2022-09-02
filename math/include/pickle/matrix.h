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
                Matrix<R, C, T> sum;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        sum.data[index] = data[index] + matrix.data[index];
                    }
                }
                return sum;
            }

            Matrix<R, C, T> operator-(const Matrix<R, C, T> &matrix) const
            {
                Matrix<R, C, T> sub;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        sub.data[index] = data[index] - matrix.data[index];
                    }
                }
                return sub;
            }

            Matrix<R, C, T> operator*(float scalar) const
            {
                Matrix<R, C, T> mul;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        mul.data[index] = data[index] * scalar;
                    }
                }
                return mul;
            }

            template <size_t NC>
            Matrix<R, NC, T> operator*(const Matrix<C, NC, T> &matrix) const
            {
                Matrix<R, NC, T> mul;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < NC; j++)
                    {
                        T value = 0;
                        for (size_t k = 0; k < C; k++)
                        {
                            value += data[i * C + k] * matrix.data[k * NC + j];
                        }
                        mul.data[i * NC + j] = value;
                    }
                }
                return mul;
            }

            Vector<R, T> operator*(const Vector<C, T> &vector) const
            {
                Vector<R, T> mul;
                for (size_t i = 0; i < R; i++)
                {
                    T value = 0;
                    for (size_t k = 0; k < C; k++)
                    {
                        value += data[i * C + k] * vector.data[k];
                    }
                    mul.data[i] = value;
                }
                return mul;
            }

            Matrix<R, C, T> operator/(float divider) const
            {
                Matrix<R, C, T> div;
                for (size_t i = 0; i < R; i++)
                {
                    for (size_t j = 0; j < C; j++)
                    {
                        size_t index = i * C + j;
                        div.data[index] = data[index] / divider;
                    }
                }
                return div;
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