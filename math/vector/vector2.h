#ifndef PICKLE_MATH_VECTOR2
#define PICKLE_MATH_VECTOR2

#include "math.h"

namespace pickle
{
    namespace math
    {
        class Vector2
        {
        public:
            Vector2(float x, float y) : x(x), y(y)
            {
            }

            Vector2(const Vector2& vector) : Vector2(vector.x, vector.y)
            {
            }

            ~Vector2() = default;

            Vector2& operator=(const Vector2& vector)
            {
                if (this == &vector)
                {
                    return *this;
                }

                this->x = vector.x;
                this->y = vector.y;
                return *this;
            }

            Vector2 operator+(const Vector2& vector) const
            {
                return Vector2(x + vector.x, y + vector.y);
            }

            Vector2 operator-(const Vector2& vector) const
            {
                return Vector2(x - vector.x, y - vector.y);
            }

            Vector2 operator*(float scalar) const
            {
                return Vector2(x * scalar, y * scalar);
            }

            Vector2 operator/(float divider) const
            {
                return Vector2(x / divider, y / divider);
            }

            float dot(const Vector2& vector) const
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