#ifndef RAYTRACING_DIRECT_LIGHT_H
#define RAYTRACING_DIRECT_LIGHT_H

#include <pickle/math.h>
#include <algorithm>

#include "light.h"

class DirectLight : public Light
{
public:
    DirectLight(float maxIntensity, pickle::math::Vector<3, float> direction) : Light(maxIntensity), direction(normalize(direction))
    {
    }

    virtual float getIntensity(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal) const override
    {
        return std::clamp(dot(-direction, normal) * maxIntensity, 0.0f, 1.0f);
    }

private:
    pickle::math::Vector<3, float> direction;
};

#endif