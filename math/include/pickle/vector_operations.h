#ifndef PICKLE_MATH_VECTOR_OPERATIONS
#define PICKLE_MATH_VECTOR_OPERATIONS

#include "vector.h"

namespace pickle
{
    namespace math
    {
        template <typename TYPE>
        Vector<3, TYPE> cross(const Vector<3, TYPE> &first, const Vector<3, TYPE> &second)
        {
            return Vector<3, TYPE>({first.data[1] * second.data[2] - first.data[2] * second.data[1],
                                    -first.data[0] * second.data[2] + first.data[2] * second.data[0],
                                    first.data[0] * second.data[1] - first.data[1] * second.data[0]});
        }

        template <size_t SIZE, typename TYPE>
        TYPE dot(const Vector<SIZE, TYPE> &first, const Vector<SIZE, TYPE> &second)
        {
            TYPE result = 0;
            for (size_t i = 0; i < SIZE; i++)
            {
                result += first.data[i] * second.data[i];
            }
            return result;
        }

        template <size_t SIZE, typename TYPE>
        Vector<SIZE, TYPE> reflect(const Vector<SIZE, TYPE> &vector, const Vector<SIZE, TYPE> &norm)
        {
            return vector - (norm * 2 * (dot(vector, norm) / dot(norm, norm)));
        }

        template <size_t SIZE, typename TYPE>
        TYPE length(const Vector<SIZE, TYPE> &vector)
        {
            TYPE lenSq = 0;
            for (size_t i = 0; i < SIZE; i++)
            {
                TYPE value = vector.data[i];
                lenSq += value * value;
            }
            return sqrt(lenSq);
        }

        template <size_t SIZE, typename TYPE>
        Vector<SIZE, TYPE> normalize(const Vector<SIZE, TYPE> &vector)
        {
            Vector<SIZE, TYPE> result;
            TYPE len = length(vector);
            for (size_t i = 0; i < SIZE; i++)
            {
                result.data[i] = vector.data[i] / len;
            }
            return result;
        }

        template <typename TYPE>
        Quaternion<TYPE> toQuaternion(const Vector<4, TYPE> &vector)
        {
            return Quaternion<TYPE>(vector.data[3], vector.data[0], vector.data[1], vector.data[2]);
        }
    }
}

#endif