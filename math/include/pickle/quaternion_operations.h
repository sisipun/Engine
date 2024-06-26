#ifndef PICKLE_MATH_QUATERNION_OPERATIONS
#define PICKLE_MATH_QUATERNION_OPERATIONS

#include <cmath>

#include "quaternion.h"
#include "vector.h"
#include "matrix.h"

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
            return first * second;
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
            TYPE squareLength = quaternion.squareLength();
            if (squareLength == 1)
            {
                return quaternion;
            }

            return quaternion / sqrt(squareLength);
        }

        template <typename TYPE>
        Quaternion<TYPE> lerp(const Quaternion<TYPE> &first, const Quaternion<TYPE> &second, TYPE a)
        {
            return (first * (1 - a)) + (second * a);
        }

        template <typename TYPE>
        Vector<4, TYPE> toVector(const Quaternion<TYPE> &quaternion)
        {
            return Vector<4, TYPE>({quaternion.x, quaternion.y, quaternion.z, quaternion.w});
        }

        template <typename TYPE>
        Matrix<3, 3, TYPE> toMatrix3x3(const Quaternion<TYPE> &quaternion)
        {
            Quaternion<TYPE> normQuaternion = normalize(quaternion);

            TYPE x2 = normQuaternion.x + normQuaternion.x;
            TYPE y2 = normQuaternion.y + normQuaternion.y;
            TYPE z2 = normQuaternion.z + normQuaternion.z;
            TYPE xx2 = normQuaternion.x * x2;
            TYPE xy2 = normQuaternion.x * y2;
            TYPE xz2 = normQuaternion.x * z2;
            TYPE yx2 = normQuaternion.y * x2;
            TYPE yy2 = normQuaternion.y * y2;
            TYPE yz2 = normQuaternion.y * z2;
            TYPE zx2 = normQuaternion.z * x2;
            TYPE zy2 = normQuaternion.z * y2;
            TYPE zz2 = normQuaternion.z * z2;
            TYPE wx2 = normQuaternion.w * x2;
            TYPE wy2 = normQuaternion.w * y2;
            TYPE wz2 = normQuaternion.w * z2;

            return Matrix<3, 3, TYPE>({1 - yy2 - zz2, xy2 - wz2, xz2 - wy2,
                                       xy2 - wz2, 1 - xx2 - zz2, yz2 + wx2,
                                       xz2 + wy2, yz2 - wx2, 1 - xx2 - yy2});
        }

        template <typename TYPE>
        Matrix<4, 4, TYPE> toMatrix4x4(const Quaternion<TYPE> &quaternion)
        {
            return toMatrix3x3(quaternion)
                .addRowDimension<3>(Matrix<1, 3, TYPE>({0, 0, 0}))
                .addColumnDimension<3>(Matrix<4, 1, TYPE>({0, 0, 0, 1}));
        }
    }
}

#endif