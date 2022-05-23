#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H

#include <pickle/math.h>

class Light
{
public:
    Light(float maxIntensity) : maxIntensity(maxIntensity)
    {
    }

    virtual ~Light() = default;

    virtual float getIntensity(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal, pickle::math::Vector<3, float> view, float shininess) const = 0;

protected:
    float maxIntensity;
};

#endif