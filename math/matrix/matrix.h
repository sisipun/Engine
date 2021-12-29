#ifndef PICKLE_MATH_MATRIX
#define PICKLE_MATH_MATRIX

namespace pickle
{
    namespace math
    {
        template <int R, int C, typename T>
        class Matrix
        {
        public:
            Matrix() : data{0.0f}
            {
            }

            Matrix(const T (&data)[R * C])
            {
                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        int index = i * C + j;
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

                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        int index = i * C + j;
                        this->data[index] = matrix.data[index];
                    }
                }
                return *this;
            }

            Matrix<R, C, T> operator+(const Matrix<R, C, T> &matrix)
            {
                Matrix<R, C, T> sum;
                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        int index = i * C + j;
                        sum.data[index] = data[index] + matrix.data[index];
                    }
                }
                return sum;
            }

            Matrix<R, C, T> operator-(const Matrix<R, C, T> &matrix)
            {
                Matrix<R, C, T> sub;
                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        int index = i * C + j;
                        sub.data[index] = data[index] - matrix.data[index];
                    }
                }
                return sub;
            }

            Matrix<R, C, T> operator*(float scalar) const
            {
                Matrix<R, C, T> mul;
                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        int index = i * C + j;
                        mul.data[index] = data[index] * scalar;
                    }
                }
                return mul;
            }

            Matrix<R, C, T> operator/(float divider) const
            {
                Matrix<R, C, T> div;
                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        int index = i * C + j;
                        div.data[index] = data[index] / divider;
                    }
                }
                return div;
            }

        public:
            T data[R * C];
        };
    }
}

#endif