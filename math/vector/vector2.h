#ifndef PICKLE_MATH_VECTOR_2
#define PICKLE_MATH_VECTOR_2

#include "vector.h"
#include "math.h"

namespace pickle
{
    namespace math
    {
        template<>
        class Vector<2>
        {
        public:
            Vector(float x, float y) : x(x), y(y)
            {
            }

            Vector(const Vector& vector) : x(vector.x), y(vector.y)
            {
            }

            ~Vector() = default;

            Vector<2>& operator=(const Vector<2>& vector)
            {
                if (this == &vector)
                {
                    return *this;
                }

                this->x = vector.x;
                this->y = vector.y;
                return *this;
            }

            Vector<2> operator+(const Vector<2>& vector) const
            {
                return Vector<2>(x + vector.x, y + vector.y);
            }

            Vector<2> operator-(const Vector<2>& vector) const
            {
                return Vector<2>(x - vector.x, y - vector.y);
            }

            Vector<2> operator*(float scalar) const
            {
                return Vector<2>(x * scalar, y * scalar);
            }

            Vector<2> operator/(float divider) const
            {
                return Vector<2>(x / divider, y / divider);
            }

            Vector<2> reflect(const Vector<2>& norm) const
            {
                return *this - (norm * 2 * (this->dot(norm) / norm.dot(norm)));
            }

            float dot(const Vector<2>& vector) const
            {
                return x * vector.x + y * vector.y;
            }

            virtual float length() const
            {
                return sqrt(x * x + y * y);
            }

            virtual void normalize()
            {
                float len = length();
                x /= len;
                y /= len;
            }

        public:
            float x, y;
        };
    }
}

#endif