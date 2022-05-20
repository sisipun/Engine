#ifndef RAYTRACING_SHAPE_H
#define RAYTRACING_SHAPE_H

#include <pickle/math.h>
#include "color.h"

class Shape
{
public:
    Shape(Color color);
    virtual ~Shape();

    virtual pickle::math::Vector<2, float> intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray) const = 0;

    Color getColor() const;

private:
    Color color;
};

#endif