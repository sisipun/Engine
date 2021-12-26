#ifndef PICKLE_MATH_VECTOR_3
#define PICKLE_MATH_VECTOR_3

#include "vector.h"
#include "math.h"

namespace pickle
{
    namespace math
    {
        template<>
        class Vector<3>
        {
        public:
            Vector(float x, float y, float z) : x(x), y(y), z(z)
            {
            }

            Vector(const Vector<3>& vector) : x(vector.x), y(vector.y), z(vector.z)
            {
            }

            ~Vector() = default;

            Vector& operator=(const Vector<3>& vector)
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

            Vector<3> operator+(const Vector<3>& vector) const
            {
                return Vector<3>(x + vector.x, y + vector.y, z + vector.z);
            }

            Vector<3> operator-(const Vector<3>& vector) const
            {
                return Vector<3>(x - vector.x, y - vector.y, z - vector.z);
            }

            Vector<3> operator*(float scalar) const
            {
                return Vector<3>(x * scalar, y * scalar, z * scalar);
            }

            Vector<3> operator/(float divider) const
            {
                return Vector<3>(x / divider, y / divider, z / divider);
            }

            float dot(const Vector<3>& vector) const
            {
                return x * vector.x + y * vector.y + z * vector.z;
            }

            Vector<3> cross(const Vector<3>& vector)
            {
                return Vector<3>(y * vector.z - z * vector.y, -x * vector.z + z * vector.x, x * vector.y - y * vector.x);
            }

            Vector<3> reflect(const Vector<3>& norm) const
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