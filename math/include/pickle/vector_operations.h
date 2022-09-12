#ifndef PICKLE_MATH_VECTOR_OPERATIONS
#define PICKLE_MATH_VECTOR_OPERATIONS

#include "vector.h"

namespace pickle
{
    namespace math
    {
        template <typename T>
        Vector<3, T> cross(const Vector<3, T> &first, const Vector<3, T> &second)
        {
            return Vector<3, T>({first.data[1] * second.data[2] - first.data[2] * second.data[1],
                                 -first.data[0] * second.data[2] + first.data[2] * second.data[0],
                                 first.data[0] * second.data[1] - first.data[1] * second.data[0]});
        }

        template <size_t D, typename T>
        float dot(const Vector<D, T> &first, const Vector<D, T> &second)
        {
            float result = 0;
            for (size_t i = 0; i < D; i++)
            {
                result += first.data[i] * second.data[i];
            }
            return result;
        }

        template <size_t D, typename T>
        Vector<D, T> reflect(const Vector<D, T> &vector, const Vector<D, T> &norm)
        {
            return vector - (norm * 2 * (dot(vector, norm) / dot(norm, norm)));
        }

        template <size_t D, typename T>
        float length(const Vector<D, T> &vector)
        {
            float lenSq = 0;
            for (size_t i = 0; i < D; i++)
            {
                T value = vector.data[i];
                lenSq += value * value;
            }
            return sqrt(lenSq);
        }

        template <size_t D, typename T>
        Vector<D, T> normalize(const Vector<D, T> &vector)
        {
            Vector<D, T> result;
            float len = length(vector);
            for (size_t i = 0; i < D; i++)
            {
                result.data[i] = vector.data[i] / len;
            }
            return result;
        }
    }
}

#endif