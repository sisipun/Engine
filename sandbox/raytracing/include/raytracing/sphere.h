#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <pickle/math.h>

#include "shape.h"
#include "color.h"

class Sphere : public Shape
{
public:
    Sphere(pickle::math::Vector<3, float> center, float radius, Color color);

    virtual pickle::math::Vector<2, float> intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray) override;

private:
    pickle::math::Vector<3, float> center;
    float radius;
    Color color;
};

#endif