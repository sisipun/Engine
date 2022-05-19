#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

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

#endif