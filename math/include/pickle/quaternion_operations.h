#ifndef PICKLE_MATH_QUATERNION_OPERATIONS
#define PICKLE_MATH_QUATERNION_OPERATIONS

#include "quaternion.h"

namespace pickle
{
    namespace math
    {
        template <typename TYPE>
        TYPE dot(const Quaternion<TYPE> &first, const Quaternion<TYPE> &second)
        {
            return first.w * second.w + first.x * second.x + first.y * second.y + first.z * second.z;
        }

        template <typename TYPE>
        Quaternion<TYPE> cross(const Quaternion<TYPE> &first, const Quaternion<TYPE> &second)
        {
            return Quaternion<TYPE>(
                first.w * second.w - first.x * second.x - first.y * second.y - first.z * second.z,
                first.w * second.x + first.x * second.w + first.y * second.z - first.z * second.y,
                first.w * second.y + first.y * second.w + first.z * second.x - first.x * second.z,
                first.w * second.z + first.z * second.w + first.x * second.y - first.y * second.x,
            );
        }

        template <typename TYPE>
        Quaternion<TYPE> conjugate(const Quaternion<TYPE> &quaternion)
        {
            return Quaternion<TYPE>(quaternion.w, -quaternion.x, -quaternion.y, -quaternion.z);
        }

        template <typename TYPE>
        Quaternion<TYPE> inverse(const Quaternion<TYPE> &quaternion)
        {
            return conjugate(quaternion) / dot(quaternion, quaternion);
        }

        template <typename TYPE>
        Quaternion<TYPE> normalize(const Quaternion<TYPE> &quaternion)
        {
            return quaternion / quaternion.norm();
        }
    }
}

#endif