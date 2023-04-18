#ifndef PICKLE_MATH_VECTOR
#define PICKLE_MATH_VECTOR

#include <cmath>

#include "quaternion.h"

namespace pickle
{
    namespace math
    {
        template <size_t SIZE, typename TYPE>
        class Vector
        {
        public:
            Vector() : data{0}
            {
            }

            Vector(const TYPE (&data)[SIZE])
            {
                for (size_t i = 0; i < SIZE; i++)
                {
                    this->data[i] = data[i];
                }
            }

            Vector(const Vector<SIZE, TYPE> &vector)
            {
                for (size_t i = 0; i < SIZE; i++)
                {
                    data[i] = vector.data[i];
                }
            }

            ~Vector() = default;

            Vector &operator=(const Vector<SIZE, TYPE> &vector)
            {
                if (this == &vector)
                {
                    return *this;
                }

                for (size_t i = 0; i < SIZE; i++)
                {
                    data[i] = vector.data[i];
                }
                return *this;
            }

            Vector<SIZE, TYPE> operator+(const Vector<SIZE, TYPE> &vector) const
            {
                Vector<SIZE, TYPE> result;
                for (size_t i = 0; i < SIZE; i++)
                {
                    result.data[i] = data[i] + vector.data[i];
                }
                return result;
            }

            Vector<SIZE, TYPE> operator-(const Vector<SIZE, TYPE> &vector) const
            {
                Vector<SIZE, TYPE> result;
                for (size_t i = 0; i < SIZE; i++)
                {
                    result.data[i] = this->data[i] - vector.data[i];
                }
                return result;
            }

            Vector<SIZE, TYPE> operator-() const
            {
                Vector<SIZE, TYPE> result;
                for (size_t i = 0; i < SIZE; i++)
                {
                    result.data[i] = -this->data[i];
                }
                return result;
            }

            Vector<SIZE, TYPE> operator*(TYPE scalar) const
            {
                Vector<SIZE, TYPE> result;
                for (size_t i = 0; i < SIZE; i++)
                {
                    result.data[i] = data[i] * scalar;
                }
                return result;
            }

            Vector<SIZE, TYPE> operator/(TYPE divider) const
            {
                Vector<SIZE, TYPE> result;
                for (size_t i = 0; i < SIZE; i++)
                {
                    result.data[i] = data[i] / divider;
                }
                return result;
            }

            bool operator==(Vector<SIZE, TYPE> vector) const
            {
                for (size_t i = 0; i < SIZE; i++)
                {
                    if (data[i] != vector.data[i])
                    {
                        return false;
                    }
                }

                return true;
            }

            bool operator!=(Vector<SIZE, TYPE> vector) const
            {
                return !(*this == vector);
            }

            template <size_t POSITION>
            typename std::enable_if<(POSITION < SIZE), Vector<SIZE - 1, TYPE>>::type cutDimension() const
            {
                return cutDimension<POSITION, 1>();
            }

            template <size_t POSITION, size_t COUNT>
            typename std::enable_if<POSITION + COUNT <= SIZE, Vector<SIZE - COUNT, TYPE>>::type cutDimension() const
            {
                Vector<SIZE - COUNT, TYPE> result;
                for (size_t i = 0, ci = 0; i < SIZE; i++)
                {
                    if (i < POSITION || i >= POSITION + COUNT)
                    {
                        result.data[ci] = data[i];
                        ci++;
                    }
                }
                return result;
            }

            template <size_t POSITION, size_t COUNT>
            typename std::enable_if<(COUNT > 1) && POSITION + COUNT <= SIZE, Vector<SIZE - COUNT, TYPE>>::type extract() const
            {
                Vector<SIZE - COUNT, TYPE> result;
                for (size_t i = 0, ri = 0; i < SIZE; i++)
                {
                    if (i >= POSITION && i < POSITION + COUNT)
                    {
                        result.data[ri] = data[i];
                        ri++;
                    }
                }
                return result;
            }

            template <size_t POSITION>
            typename std::enable_if<POSITION <= SIZE, Vector<SIZE + 1, TYPE>>::type addDimension(TYPE value) const
            {
                return addDimension<POSITION, 1>(Vector<1, TYPE>({value}));
            }

            template <size_t POSITION, size_t COUNT>
            typename std::enable_if<POSITION <= SIZE, Vector<SIZE + COUNT, TYPE>>::type addDimension(Vector<COUNT, TYPE> value) const
            {
                Vector<SIZE + COUNT, TYPE> result;
                size_t ri = 0;
                for (size_t i = 0; i < POSITION; i++, ri++)
                {
                    result.data[ri] = data[i];
                }

                for (size_t i = 0; i < COUNT; i++, ri++)
                {
                    result.data[ri] = value.data[i];
                }

                for (size_t i = POSITION; i < SIZE; i++, ri++)
                {
                    result.data[ri] = data[i];
                }

                return result;
            }

            template <size_t POSITION>
            typename std::enable_if<(POSITION < SIZE), Vector<SIZE, TYPE>>::type replace(TYPE value) const
            {
                return replace<POSITION, 1>(Vector<1, TYPE>({value}));
            }

            template <size_t POSITION, size_t COUNT>
            typename std::enable_if<POSITION + COUNT <= SIZE, Vector<SIZE, TYPE>>::type replace(Vector<COUNT, TYPE> value) const
            {
                Vector<SIZE, TYPE> result(data);
                for (size_t i = 0; i < COUNT; i++)
                {
                    result.data[i + POSITION] = value.data[i];
                }
                return result;
            }

            size_t size() const
            {
                return SIZE;
            }

        public:
            TYPE data[SIZE];
        };
    }
}

#endif