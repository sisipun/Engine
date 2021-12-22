#ifndef PICKLE_MATH_VECTOR3
#define PICKLE_MATH_VECTOR3

#include "vector2.h"
#include "math.h"

namespace pickle
{
    namespace math
    {
        class Vector3 : public Vector2
        {
        public:
            Vector3(float x, float y, float z) : Vector2(x, y), z(z)
            {
            }

            Vector3 operator+(Vector3 vector) const
            {
                return Vector3(x + vector.x, y + vector.y, z + vector.z);
            }

            Vector3 operator-(Vector3 vector) const
            {
                return Vector3(x - vector.x, y - vector.y, z - vector.z);
            }

            Vector3 operator*(float scalar) const
            {
                return Vector3(x * scalar, y * scalar, z * scalar);
            }

            Vector3 operator/(float divider) const
            {
                return Vector3(x / divider, y / divider, z / divider);
            }

            virtual float length() const override
            {
                return sqrt(x * x + y * y + z * z);
            }

            virtual void normalize() override
            {
                float len = length();
                x /= len;
                y /= len;
                z /= len;
            }

        public:
            float z;
        };
    }
}

#endif