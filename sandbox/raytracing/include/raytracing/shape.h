#ifndef RAYTRACING_SHAPE_H
#define RAYTRACING_SHAPE_H

#include <pickle/math.h>
#include "color.h"

class Shape
{
public:
    Shape(Color color, float shininess) : color(color), shininess(shininess)
    {
    }

    virtual ~Shape() = default;

    virtual pickle::math::Vector<2, float> intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray) const = 0;

    virtual pickle::math::Vector<3, float> getNormal(pickle::math::Vector<3, float> point) const = 0;

    Color getColor() const
    {
        return color;
    }

    float getShininess() const
    {
        return shininess;
    }

private:
    Color color;
    float shininess;
};

#endif