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

            bool operator==(Vector<D, T> vector)
            {
                for (size_t i = 0; i < D; i++)
                {
                    if (data[i] != vector.data[i])
                    {
                        return false;
                    }
                }

                return true;
            }

            bool operator!=(Vector<D, T> vector)
            {
                return !(*this == vector);
            }

            template <int P>
            typename std::enable_if<P >= 0 && P <= D - 1, Vector<D - 1, T>>::type cutDimension()
            {
                return cutDimension<P, P>();
            }

            template <int L, int R>
            typename std::enable_if<L <= R && L >= 0 && R <= D - 1, Vector<D - (R - L + 1), T>>::type cutDimension()
            {
                Vector<D - (R - L + 1), T> cutted;
                size_t cuttedIndex = 0;
                for (size_t i = 0; i < D; i++)
                {
                    if (i >= L && i <= R)
                    {
                        continue;
                    }

                    cutted.data[cuttedIndex] = data[i];
                    cuttedIndex++;
                }
                return cutted;
            }

            template <int P>
            typename std::enable_if<P >= 0 && P <= D, Vector<D + 1, T>>::type addDimension(T value)
            {
                return addDimension<P, 1>(Vector<1, T>({value}));
            }

            template <int P, int S>
            typename std::enable_if<P >= 0 && P <= D, Vector<D + S, T>>::type addDimension(Vector<S, T> value)
            {
                Vector<D + S, T> added;
                size_t addedIndex = 0;
                for (size_t i = 0; i < P; i++, addedIndex++)
                {
                    added.data[addedIndex] = data[i];
                }

                for (size_t i = 0; i < S; i++, addedIndex++)
                {
                    added.data[addedIndex] = value.data[i];
                }

                for (size_t i = P; i < D; i++, addedIndex++)
                {
                    added.data[addedIndex] = data[i];
                }

                return added;
            }

            size_t size() const
            {
                return D;
            }

        public:
            T data[D];
        };
    }
}

#endif