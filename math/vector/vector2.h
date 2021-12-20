#ifndef PICKLE_MATH_VECTOR2
#define PICKLE_MATH_VECTOR2

namespace pickle
{
    namespace math
    {
        template <typename T>
        class Vector2
        {
        public:
            Vector2(T x, T y) : x(x), y(y)
            {
            }

            Vector2 operator+(Vector2 vector)
            {
                return Vector2(x + vector.x, y + vector.y);
            }

            Vector2 operator-(Vector2 vector)
            {
                return Vector2(x - vector.x, y - vector.y);
            }

        public:
            T x, y;
        };
    }
}

#endif