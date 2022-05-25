#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include <algorithm>

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

    Color operator+(Color color)
    {
        return {
            static_cast<unsigned char>(std::clamp(color.r + r, 0, 0xFF)),
            static_cast<unsigned char>(std::clamp(color.g + g, 0, 0xFF)),
            static_cast<unsigned char>(std::clamp(color.b + b, 0, 0xFF)),
            static_cast<unsigned char>(std::clamp(color.a + a, 0, 0xFF))};
    }

    unsigned char r, g, b, a;
};

#endif