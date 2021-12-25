#ifndef PICKLE_MATH_VECTOR3
#define PICKLE_MATH_VECTOR3

#include "math.h"

namespace pickle
{
    namespace math
    {
        class Vector3
        {
        public:
            Vector3(float x, float y, float z) : x(x), y(y), z(z)
            {
            }

            Vector3(const Vector3& vector) : Vector3(vector.x, vector.y, vector.z)
            {
            }

            ~Vector3() = default;

            Vector3& operator=(const Vector3& vector)
            {
                if (this == &vector)
                {
                    return *this;
                }

                this->x = vector.x;
                this->y = vector.y;
                this->z = vector.z;
                return *this;
            }

            Vector3 operator+(const Vector3& vector) const
            {
                return Vector3(x + vector.x, y + vector.y, z + vector.z);
            }

            Vector3 operator-(const Vector3& vector) const
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

            float dot(const Vector3& vector) const
            {
                return x * vector.x + y * vector.y + z * vector.z;
            }

            Vector3 cross(const Vector3& vector)
            {
                return Vector3(y * vector.z - z * vector.y, -x * vector.z + z * vector.x, x * vector.y - y * vector.x);
            }

            Vector3 reflect(const Vector3& norm) const
            {
                return *this - (norm * 2 * (this->dot(norm) / norm.dot(norm)));
            }

            virtual float length() const
            {
                return sqrt(x * x + y * y + z * z);
            }

            virtual void normalize()
            {
                float len = length();
                x /= len;
                y /= len;
                z /= len;
            }

        public:
            float x, y, z;
        };
    }
}

#endif