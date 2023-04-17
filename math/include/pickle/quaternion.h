#ifndef PICKLE_MATH_QUATERNION
#define PICKLE_MATH_QUATERNION

#include <cmath>

namespace pickle
{
    namespace math
    {
        template <typename TYPE>
        class Quaternion
        {
        public:
            Quaternion() : w(0), x(0), y(0), z(0)
            {
            }

            Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z)
            {
            }

            ~Quaternion() = default;

            Quaternion<TYPE> &operator=(const Quaternion<TYPE> &quaternion)
            {
                if (this == &quaternion)
                {
                    return *this;
                }

                w = quaternion.w;
                x = quaternion.x;
                y = quaternion.y;
                z = quaternion.z;
                return *this;
            }

            Quaternion<TYPE> operator+(const Quaternion<TYPE> &quaternion) const
            {
                return Quaternion<TYPE>(w + quaternion.w, x + quaternion.x, y + quaternion.y, z + quaternion.z);
            }

            Quaternion<TYPE> operator-(const Quaternion<TYPE> &quaternion) const
            {
                return Quaternion<TYPE>(w - quaternion.w, x - quaternion.x, y - quaternion.y, z - quaternion.z);
            }

            Quaternion<TYPE> operator*(TYPE scalar) const
            {
                return Quaternion<TYPE>(w * scalar, x * scalar, y * scalar, z * scalar);
            }

            Quaternion<TYPE> operator/(TYPE divider) const
            {
                return Quaternion<TYPE>(w / divider, x / divider, y / divider, z / divider);
            }

            bool operator==(const Quaternion<TYPE> &quaternion) const
            {
                return w == quaternion.w && x == quaternion.x && y == quaternion.y && z == quaternion.z;
            }

            bool operator!=(Quaternion<TYPE> vector) const
            {
                return !(*this == vector);
            }

            TYPE norm() const
            {
                return sqrt(w * w + x * x + y * y + z * z);
            }

        public:
            T w;
            T x;
            T y;
            T z;
        };
    }
}

#endif