#ifndef RAYTRACING_SHAPE_H
#define RAYTRACING_SHAPE_H

#include <pickle/math.h>

class Shape
{
public:
    virtual ~Shape()
    {
    }

    virtual pickle::math::Vector<2, float> intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray) = 0;
};

#endif