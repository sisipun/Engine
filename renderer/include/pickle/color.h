#ifndef PICKLE_RENDERER_COLOR_H
#define PICKLE_RENDERER_COLOR_H

namespace pickle
{
    namespace renderer
    {
        struct Color
        {
            Color operator*(float value)
            {
                return {
                    static_cast<unsigned char>(r * value),
                    static_cast<unsigned char>(g * value),
                    static_cast<unsigned char>(b * value),
                    a};
            }

            unsigned char r, g, b, a;
        };
    }
}

#endif