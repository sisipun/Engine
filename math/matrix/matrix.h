#ifndef PICKLE_MATH_MATRIX
#define PICKLE_MATH_MATRIX

namespace pickle
{
    namespace math
    {
        template <int R, int C>
        class Matrix
        {
        public:
            Matrix() : data{0.0f}
            {
            }

            Matrix(const float (&data)[R * C])
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

            Matrix<R, C> operator+(const Matrix<R, C> &matrix)
            {
                Matrix<R, C> sum;
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

            Matrix<R, C> operator-(const Matrix<R, C> &matrix)
            {
                Matrix<R, C> sub;
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

        public:
            float data[R * C];
        };
    }
}

#endif