#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <pickle/math.h>

#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere(pickle::math::Vector<3, float> center, float radius, Color color) : Shape(color), center(center), radius(radius)
    {
    }

    virtual pickle::math::Vector<2, float> intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray) const override;

    virtual pickle::math::Vector<3, float> getNormal(pickle::math::Vector<3, float> point) const override;

private:
    pickle::math::Vector<3, float> center;
    float radius;
};

#endif