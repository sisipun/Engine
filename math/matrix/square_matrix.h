#ifndef PICKLE_MATH_SQUARE_MATRIX
#define PICKLE_MATH_SQUARE_MATRIX

#include "matrix.h"

namespace pickle
{
    namespace math
    {
        template <int D, typename T>
        class SquareMatrix : public Matrix<D, D, T>
        {
        public:
            static SquareMatrix<D, T> identity()
            {
                SquareMatrix<D, T> identityMatrix;
                for (int i = 0; i < D; i++)
                {
                    identityMatrix.data[i * D + i] = 1;
                }
                return identityMatrix;
            }
        };
    }
}

#endif