#ifndef PICKLE_MATH_COMMON_OPERATIONS
#define PICKLE_MATH_COMMON_OPERATIONS

#include <cmath>
#include <numbers>

#include "vector.h"
#include "vector_operations.h"
#include "matrix.h"

namespace pickle
{
    namespace math
    {
        template <typename T>
        T radians(const T degrees)
        {
            return static_cast<T>((std::numbers::pi / 180.0) * degrees);
        }

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
        Matrix<4, 4, T> rotate(const Matrix<4, 4, T> &base, const T angle, const Vector<3, T> &axis)
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
        Matrix<4, 4, T> ortho(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax)
        {
            return Matrix<4, 4, T>({2.0f / (xMax - xMin), 0.0f, 0.0f, -(xMax + xMin) / (xMax - xMin),
                                    0.0f, 2.0f / (yMax - yMin), 0.0f, -(yMax + yMin) / (yMax - yMin),
                                    0.0f, 0.0f, -2.0f / (zMax - zMin), -(zMax + zMin) / (zMax - zMin),
                                    0.0f, 0.0f, 0.0f, 1.0f});
        }

        template <typename T>
        Matrix<4, 4, T> perspective(float fov, float aspect, T near, T far)
        {
            return Matrix<4, 4, T>({1.0f / (aspect * tan(fov / 2.0f)), 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f / tan(fov / 2.0f), 0.0f, 0.0f,
                                    0.0f, 0.0f, -(far + near) / (far - near), -2.0f * far * near / (far - near),
                                    0.0f, 0.0f, -1.0f, 0.0f});
        }
    }
}
#endif