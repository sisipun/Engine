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

        template <int D, typename T>
        float dot(const Vector<D, T> &first, const Vector<D, T> &second)
        {
            float dotValue = 0;
            for (int i = 0; i < D; i++)
            {
                dotValue += first.data[i] * second.data[i];
            }
            return dotValue;
        }

        template <int D, typename T>
        Vector<D, T> reflect(const Vector<D, T> &vector, const Vector<D, T> &norm)
        {
            return vector - (norm * 2 * (dot(vector, norm) / dot(norm, norm)));
        }

        template <int D, typename T>
        float length(const Vector<D, T> &vector)
        {
            float lenSq = 0;
            for (int i = 0; i < D; i++)
            {
                T value = vector.data[i];
                lenSq += value * value;
            }
            return sqrt(lenSq);
        }

        template <int D, typename T>
        Vector<D, T> normalize(const Vector<D, T> &vector)
        {
            Vector<D, T> norm;
            float len = length(vector);
            for (int i = 0; i < D; i++)
            {
                norm.data[i] = vector.data[i] / len;
            }
            return norm;
        }
    }
}

#endif