#ifndef PICKLE_MATH_MATRIX_2X2
#define PICKLE_MATH_MATRIX_2X2

#include "matrix.h"
#include "../vector/vector2.h"

namespace pickle
{
    namespace math
    {
        template<>
        class Matrix<2, 2>
        {
            private:
                Vector<2> data[2];
        };
    }
}

#endif