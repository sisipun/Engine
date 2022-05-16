#ifndef PICKLE_MATH_COMMON_OPERATIONS
#define PICKLE_MATH_COMMON_OPERATIONS

#include <cmath>

#include "vector.h"
#include "vector_operations.h"
#include "matrix.h"

namespace pickle
{
    namespace math
    {
        template <typename T>
        Matrix<4, 4, T> translate(const Matrix<4, 4, T> &base, const Vector<3, T> &translation)
        {
            return base * Matrix<4, 4, T>({1, 0, 0, translation.data[0],
                                           0, 1, 0, translation.data[1],
                                           0, 0, 1, translation.data[2],
                                           0, 0, 0, 1});
        }

        template <typename T>
        Matrix<4, 4, T> scale(const Matrix<4, 4, T> &base, const Vector<3, T> &scale)
        {
            return base * Matrix<4, 4, T>({scale.data[0], 0, 0, 0,
                                           0, scale.data[1], 0, 0,
                                           0, 0, scale.data[2], 0,
                                           0, 0, 0, 1});
        }

        template <typename T>
        Matrix<4, 4, T> rotate(const Matrix<4, 4, T> &base, T angle, const Vector<3, T> &axis)
        {
            T x = axis.data[0];
            T y = axis.data[1];
            T z = axis.data[2];
            T cosAngle = cos(angle);
            T sinAngle = sin(angle);
            return base * Matrix<4, 4, T>({cosAngle + (1 - cosAngle) * x * x, (1 - cosAngle) * x * y - sinAngle * z, (1 - cosAngle) * x * z + sinAngle * y, 0,
                                           (1 - cosAngle) * x * y + sinAngle * z, cosAngle + (1 - cosAngle) * y * y, (1 - cosAngle) * y * z - sinAngle * x, 0,
                                           (1 - cosAngle) * x * z - sinAngle * y, (1 - cosAngle) * y * z + sinAngle * x, cosAngle + (1 - cosAngle) * z * z, 0,
                                           0, 0, 0, 1});
        }

        template <typename T>
        Matrix<4, 4, T> lookAt(const Vector<3, T> &position, const Vector<3, T> &target, const Vector<3, T> &worldUp)
        {
            const Vector<3, T> forward = normalize(target - position);
            const Vector<3, T> right = normalize(cross(worldUp, forward));
            const Vector<3, T> up = cross(forward, right);
            return Matrix<4, 4, T>({right.data[0], right.data[1], right.data[2], dot(-position, right),
                                    up.data[0], up.data[1], up.data[2], dot(-position, up),
                                    forward.data[0], forward.data[1], forward.data[2], dot(-position, forward),
                                    0, 0, 0, 1});
        }

        template <typename T>
        Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far)
        {
            return Matrix<4, 4, T>({2 / (right - left), 0, 0, -(right + left) / (right - left),
                                    0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
                                    0, 0, -2 / (far - near), -(far + near) / (far - near),
                                    0, 0, 0, 1});
        }
    }
}
#endif