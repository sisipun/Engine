#ifndef PICKLE_MATH_COMMON_OPERATIONS
#define PICKLE_MATH_COMMON_OPERATIONS

#include "vector/vector.h"
#include "matrix/matrix.h"

namespace pickle
{
    namespace math
    {
        template <typename T>
        Matrix<4, 4, T> translate(const Matrix<4, 4, T> &base, const Vector<3, T> translation)
        {
            return base * Matrix<4, 4, T>({1, 0, 0, translation.data[0],
                                           0, 1, 0, translation.data[1],
                                           0, 0, 1, translation.data[2],
                                           0, 0, 0, 1});
        }

        template <typename T>
        Matrix<4, 4, T> scale(const Matrix<4, 4, T> &base, const Vector<3, T> scale)
        {
            return base * Matrix<4, 4, T>({scale.data[0], 0, 0, 0,
                                           0, scale.data[1], 0, 0,
                                           0, 0, scale.data[2], 0,
                                           0, 0, 0, 1});
        }
    }
}

#endif