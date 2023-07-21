#ifndef PICKLE_MATH_ENUMS
#define PICKLE_MATH_ENUMS

namespace pickle
{
    namespace math
    {
        enum class CoordinateSystemType
        {
            LEFT_HANDED,
            RIGHT_HANDED
        };

        enum class CoordinateRange
        {
            NEGATIVE_TO_POSITIVE,
            ZERO_TO_POSITIVE
        };
    }
}

#endif