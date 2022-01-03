#ifndef PICKLE_MATH_VECTOR
#define PICKLE_MATH_VECTOR

#include "math.h"

namespace pickle
{
    namespace math
    {
        template <int D, typename T>
        class Vector
        {
        public:
            Vector() : data{0.0f}
            {
            }

            Vector(const T (&data)[D])
            {
                for (int i = 0; i < D; i++)
                {
                    this->data[i] = data[i];
                }
            }

            Vector(const Vector<D, T> &vector)
            {
                for (int i = 0; i < D; i++)
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

                for (int i = 0; i < D; i++)
                {
                    data[i] = vector.data[i];
                }
                return *this;
            }

            Vector<D, T> operator+(const Vector<D, T> &vector) const
            {
                Vector<D, T> sum;
                for (int i = 0; i < D; i++)
                {
                    sum.data[i] = data[i] + vector.data[i];
                }
                return sum;
            }

            Vector<D, T> operator-(const Vector<D, T> &vector) const
            {
                Vector<D, T> sub;
                for (int i = 0; i < D; i++)
                {
                    sub.data[i] = this->data[i] - vector.data[i];
                }
                return sub;
            }

            Vector<D, T> operator*(float scalar) const
            {
                Vector<D, T> mul;
                for (int i = 0; i < D; i++)
                {
                    mul.data[i] = data[i] * scalar;
                }
                return mul;
            }

            Vector<D, T> operator/(float divider) const
            {
                Vector<D, T> div;
                for (int i = 0; i < D; i++)
                {
                    div.data[i] = data[i] / divider;
                }
                return div;
            }

            float dot(const Vector<D, T> &vector) const
            {
                float dotValue = 0;
                for (int i = 0; i < D; i++)
                {
                    dotValue += data[i] * vector.data[i];
                }
                return dotValue;
            }

            Vector<D, T> reflect(const Vector<D, T> &norm) const
            {
                return *this - (norm * 2 * (this->dot(norm) / norm.dot(norm)));
            }

            virtual float length() const
            {
                float lenSq = 0;
                for (int i = 0; i < D; i++)
                {
                    T value = data[i];
                    lenSq += value * value;
                }
                return sqrt(lenSq);
            }

            virtual void normalize()
            {
                float len = length();
                for (int i = 0; i < D; i++)
                {
                    data[i] /= len;
                }
            }

        public:
            T data[D];
        };

        template <typename T>
        Vector<3, T> cross(const Vector<3, T> &first, const Vector<3, T> &second)
        {
            return Vector<3, T>({first.data[1] * second.data[2] - first.data[2] * second.data[1],
                                 -first.data[0] * second.data[2] + first.data[2] * second.data[0],
                                 first.data[0] * second.data[1] - first.data[1] * second.data[0]});
        }
    }
}

#endif