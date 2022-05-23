#ifndef RAYTRACING_AMBIENT_LIGHT_H
#define RAYTRACING_AMBIENT_LIGHT_H

#include <pickle/math.h>

#include "light.h"

class AmbientLight : public Light
{
public:
    AmbientLight(float maxIntensity) : Light(maxIntensity)
    {
    }

    virtual float getIntensity(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal, pickle::math::Vector<3, float> view, float shininess) const override
    {
        return maxIntensity;
    }
};

#endif