#ifndef PICKLE_MATH_VECTOR
#define PICKLE_MATH_VECTOR

#include <cmath>

namespace pickle
{
    namespace math
    {
        template <size_t D, typename T>
        class Vector
        {
        public:
            Vector() : data{0}
            {
            }

            Vector(const T (&data)[D])
            {
                for (size_t i = 0; i < D; i++)
                {
                    this->data[i] = data[i];
                }
            }

            Vector(const Vector<D, T> &vector)
            {
                for (size_t i = 0; i < D; i++)
                {
                    data[i] = vector.data[i];
                }
            }

            ~Vector() = default;

            Vector &operator=(const Vector<D, T> &vector)
            {
                if (this == &vector)
                {
                    return *this;
                }

                for (size_t i = 0; i < D; i++)
                {
                    data[i] = vector.data[i];
                }
                return *this;
            }

            Vector<D, T> operator+(const Vector<D, T> &vector) const
            {
                Vector<D, T> sum;
                for (size_t i = 0; i < D; i++)
                {
                    sum.data[i] = data[i] + vector.data[i];
                }
                return sum;
            }

            Vector<D, T> operator-(const Vector<D, T> &vector) const
            {
                Vector<D, T> sub;
                for (size_t i = 0; i < D; i++)
                {
                    sub.data[i] = this->data[i] - vector.data[i];
                }
                return sub;
            }

            Vector<D, T> operator-() const
            {
                Vector<D, T> opposite;
                for (size_t i = 0; i < D; i++)
                {
                    opposite.data[i] = -this->data[i];
                }
                return opposite;
            }

            Vector<D, T> operator*(float scalar) const
            {
                Vector<D, T> mul;
                for (size_t i = 0; i < D; i++)
                {
                    mul.data[i] = data[i] * scalar;
                }
                return mul;
            }

            Vector<D, T> operator/(float divider) const
            {
                Vector<D, T> div;
                for (size_t i = 0; i < D; i++)
                {
                    div.data[i] = data[i] / divider;
                }
                return div;
            }

        public:
            T data[D];
        };
    }
}

#endif