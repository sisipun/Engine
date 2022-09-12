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
                Vector<D, T> result;
                for (size_t i = 0; i < D; i++)
                {
                    result.data[i] = data[i] + vector.data[i];
                }
                return result;
            }

            Vector<D, T> operator-(const Vector<D, T> &vector) const
            {
                Vector<D, T> result;
                for (size_t i = 0; i < D; i++)
                {
                    result.data[i] = this->data[i] - vector.data[i];
                }
                return result;
            }

            Vector<D, T> operator-() const
            {
                Vector<D, T> result;
                for (size_t i = 0; i < D; i++)
                {
                    result.data[i] = -this->data[i];
                }
                return result;
            }

            Vector<D, T> operator*(float scalar) const
            {
                Vector<D, T> result;
                for (size_t i = 0; i < D; i++)
                {
                    result.data[i] = data[i] * scalar;
                }
                return result;
            }

            Vector<D, T> operator/(float divider) const
            {
                Vector<D, T> result;
                for (size_t i = 0; i < D; i++)
                {
                    result.data[i] = data[i] / divider;
                }
                return result;
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

            template <size_t P>
            typename std::enable_if<(P < D), Vector<D - 1, T>>::type cutDimension()
            {
                return cutDimension<P, 1>();
            }

            template <size_t P, size_t C>
            typename std::enable_if<P + C <= D, Vector<D - C, T>>::type cutDimension()
            {
                Vector<D - C, T> result;
                for (size_t i = 0, ci = 0; i < D; i++)
                {
                    if (i < P || i >= P + C)
                    {
                        result.data[ci] = data[i];
                        ci++;
                    }
                }
                return result;
            }

            template <size_t P, size_t C>
            typename std::enable_if<(C > 1) && P + C <= D, Vector<D - C, T>>::type extract()
            {
                Vector<D - C, T> result;
                for (size_t i = 0, ri = 0; i < D; i++)
                {
                    if (i >= P && i < P + C)
                    {
                        result.data[ri] = data[i];
                        ri++;
                    }
                }
                return result;
            }

            template <size_t P>
            typename std::enable_if<P <= D, Vector<D + 1, T>>::type addDimension(T value)
            {
                return addDimension<P, 1>(Vector<1, T>({value}));
            }

            template <size_t P, size_t C>
            typename std::enable_if<P <= D, Vector<D + C, T>>::type addDimension(Vector<C, T> value)
            {
                Vector<D + C, T> result;
                size_t ri = 0;
                for (size_t i = 0; i < P; i++, ri++)
                {
                    result.data[ri] = data[i];
                }

                for (size_t i = 0; i < C; i++, ri++)
                {
                    result.data[ri] = value.data[i];
                }

                for (size_t i = P; i < D; i++, ri++)
                {
                    result.data[ri] = data[i];
                }

                return result;
            }

            template <size_t P>
            typename std::enable_if<(P < D), Vector<D, T>>::type replace(T value)
            {
                return replace<P, 1>(Vector<1, T>({value}));
            }

            template <size_t P, size_t C>
            typename std::enable_if<P + C <= D, Vector<D, T>>::type replace(Vector<C, T> value)
            {
                Vector<D, T> result(data);
                for (size_t i = 0; i < C; i++)
                {
                    result.data[i + P] = value.data[i];
                }
                return result;
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