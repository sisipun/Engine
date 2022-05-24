#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H

#include <vector>

#include <pickle/math.h>

#include "shape.h"

class Light
{
public:
    Light(float maxIntensity) : maxIntensity(maxIntensity)
    {
    }

    virtual ~Light() = default;

    virtual float getIntensity(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal, pickle::math::Vector<3, float> view, float shininess, const std::vector<std::unique_ptr<Shape> > &shapes) const = 0;

protected:
    float maxIntensity;
};

#endif