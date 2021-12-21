#ifndef PICKLE_MATH_VECTOR3
#define PICKLE_MATH_VECTOR3

#include "vector2.h"

namespace pickle
{
    namespace math
    {
        template <typename T>
        class Vector3 : public Vector2<T>
        {
        public:
            Vector3(T x, T y, T z) : Vector2<T>(x, y), z(z)
            {
            }

            Vector3<T> operator+(Vector3<T> vector)
            {
                return Vector3(Vector2<T>::x + vector.x, Vector2<T>::y + vector.y, z + vector.z);
            }

            Vector3<T> operator-(Vector3<T> vector)
            {
                return Vector3(Vector2<T>::x - vector.x, Vector2<T>::y - vector.y, z - vector.z);
            }

        public:
            T z;
        };
    }
}

#endif