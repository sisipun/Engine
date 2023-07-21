#ifndef PICKLE_MATH_COMMON_OPERATIONS
#define PICKLE_MATH_COMMON_OPERATIONS

#include <cmath>
#include <numbers>

#include "enums.h"
#include "vector.h"
#include "vector_operations.h"
#include "matrix.h"

namespace pickle
{
    namespace math
    {
        template <typename TYPE>
        TYPE radians(const TYPE degrees)
        {
            return static_cast<TYPE>((std::numbers::pi / 180.0) * degrees);
        }

        template <typename TYPE>
        Matrix<4, 4, TYPE> translate(const Matrix<4, 4, TYPE> &base, const Vector<3, TYPE> &translation)
        {
            return base * Matrix<4, 4, TYPE>({1, 0, 0, translation.data[0],
                                              0, 1, 0, translation.data[1],
                                              0, 0, 1, translation.data[2],
                                              0, 0, 0, 1});
        }

        template <typename TYPE>
        Matrix<4, 4, TYPE> scale(const Matrix<4, 4, TYPE> &base, const Vector<3, TYPE> &scale)
        {
            return base * Matrix<4, 4, TYPE>({scale.data[0], 0, 0, 0,
                                              0, scale.data[1], 0, 0,
                                              0, 0, scale.data[2], 0,
                                              0, 0, 0, 1});
        }

        template <typename TYPE>
        Matrix<4, 4, TYPE> rotate(const Matrix<4, 4, TYPE> &base, const TYPE angle, const Vector<3, TYPE> &axis)
        {
            TYPE x = axis.data[0];
            TYPE y = axis.data[1];
            TYPE z = axis.data[2];
            TYPE cosAngle = cos(angle);
            TYPE sinAngle = sin(angle);
            return base * Matrix<4, 4, TYPE>({cosAngle + (1 - cosAngle) * x * x, (1 - cosAngle) * x * y - sinAngle * z, (1 - cosAngle) * x * z + sinAngle * y, 0,
                                              (1 - cosAngle) * x * y + sinAngle * z, cosAngle + (1 - cosAngle) * y * y, (1 - cosAngle) * y * z - sinAngle * x, 0,
                                              (1 - cosAngle) * x * z - sinAngle * y, (1 - cosAngle) * y * z + sinAngle * x, cosAngle + (1 - cosAngle) * z * z, 0,
                                              0, 0, 0, 1});
        }

        template <typename TYPE>
        Matrix<4, 4, TYPE> ortho(TYPE xMin, TYPE xMax, TYPE yMin, TYPE yMax, TYPE zMin, TYPE zMax)
        {
            return Matrix<4, 4, TYPE>({2.0f / (xMax - xMin), 0.0f, 0.0f, -(xMax + xMin) / (xMax - xMin),
                                       0.0f, 2.0f / (yMax - yMin), 0.0f, -(yMax + yMin) / (yMax - yMin),
                                       0.0f, 0.0f, -2.0f / (zMax - zMin), -(zMax + zMin) / (zMax - zMin),
                                       0.0f, 0.0f, 0.0f, 1.0f});
        }

        template <CoordinateSystemType SYSTEM_TYPE, CoordinateRange Z_RANGE, typename TYPE>
        Matrix<4, 4, TYPE> perspective(float fov, float aspect, TYPE nearPlane, TYPE farPlane)
        {
            float f = 1.0f / tan(fov / 2.0f);
            float sum = Z_RANGE == CoordinateRange::ZERO_TO_POSITIVE
                            ? farPlane
                            : farPlane + nearPlane;
            float depth = SYSTEM_TYPE == CoordinateSystemType::LEFT_HANDED
                              ? farPlane - nearPlane
                              : nearPlane - farPlane;
            float multiplier = Z_RANGE == CoordinateRange::ZERO_TO_POSITIVE
                                   ? 1.0f
                                   : 2.0f;
            float sign = SYSTEM_TYPE == CoordinateSystemType::LEFT_HANDED
                             ? 1.0f
                             : -1.0f;

            return Matrix<4, 4, TYPE>({f / aspect, 0.0f, 0.0f, 0.0f,
                                       0.0f, f, 0.0f, 0.0f,
                                       0.0f, 0.0f, sum / depth, -sign * multiplier * farPlane * nearPlane / depth,
                                       0.0f, 0.0f, sign, 0.0f});
        }

        template <CoordinateSystemType SYSTEM_TYPE, typename TYPE>
        Matrix<4, 4, TYPE> lookAt(const Vector<3, TYPE> &position, const Vector<3, TYPE> &target, const Vector<3, TYPE> &up)
        {
            Vector<3, TYPE> cameraDirection = normalize(target - position);
            Vector<3, TYPE> cameraRight = SYSTEM_TYPE == CoordinateSystemType::LEFT_HANDED
                                              ? normalize(cross(up, cameraDirection))
                                              : normalize(cross(cameraDirection, up));
            Vector<3, TYPE> cameraUp = SYSTEM_TYPE == CoordinateSystemType::LEFT_HANDED
                                           ? cross(cameraDirection, cameraRight)
                                           : cross(cameraRight, cameraDirection);
            float sign = SYSTEM_TYPE == CoordinateSystemType::LEFT_HANDED
                                        ? 1.0f
                                        : -1.0f;

            return Matrix<4, 4, TYPE>({cameraRight.data[0], cameraRight.data[1], cameraRight.data[2], -dot(cameraRight, position),
                                       cameraUp.data[0], cameraUp.data[1], cameraUp.data[2], -dot(cameraUp, position),
                                       sign * cameraDirection.data[0], sign * cameraDirection.data[1], sign * cameraDirection.data[2], sign * -dot(cameraDirection, position),
                                       0.0f, 0.0f, 0.0f, 1.0f});
        }
    }
}
#endif