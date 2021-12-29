#ifndef PICKLE_MATH_VECTOR_3
#define PICKLE_MATH_VECTOR_3

#include "vector.h"
#include "math.h"

namespace pickle
{
    namespace math
    {
        template<typename T>
        class Vector<3, T>
        {
        public:
            Vector(T x, T y, T z) : x(x), y(y), z(z)
            {
            }

            Vector(const Vector<3, T>& vector) : x(vector.x), y(vector.y), z(vector.z)
            {
            }

            ~Vector() = default;

            Vector& operator=(const Vector<3, T>& vector)
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

            Vector<3, T> operator+(const Vector<3, T>& vector) const
            {
                return Vector<3, T>(x + vector.x, y + vector.y, z + vector.z);
            }

            Vector<3, T> operator-(const Vector<3, T>& vector) const
            {
                return Vector<3, T>(x - vector.x, y - vector.y, z - vector.z);
            }

            Vector<3, T> operator*(float scalar) const
            {
                return Vector<3, T>(x * scalar, y * scalar, z * scalar);
            }

            Vector<3, T> operator/(float divider) const
            {
                return Vector<3, T>(x / divider, y / divider, z / divider);
            }

            float dot(const Vector<3, T>& vector) const
            {
                return x * vector.x + y * vector.y + z * vector.z;
            }

            Vector<3, T> cross(const Vector<3, T>& vector)
            {
                return Vector<3, T>(y * vector.z - z * vector.y, -x * vector.z + z * vector.x, x * vector.y - y * vector.x);
            }

            Vector<3, T> reflect(const Vector<3, T>& norm) const
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
            T x, y, z;
        };
    }
}

#endif