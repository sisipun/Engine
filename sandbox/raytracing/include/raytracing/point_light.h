#ifndef RAYTRACING_POINT_LIGHT_H
#define RAYTRACING_POINT_LIGHT_H

#include <pickle/math.h>
#include <algorithm>

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(float maxIntensity, pickle::math::Vector<3, float> position) : Light(maxIntensity), position(position)
    {
    }

    virtual float getIntensity(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal) const override
    {
        return std::clamp(dot(-normalize(point - position), normal) * maxIntensity, 0.0f, 1.0f);
    }

private:
    pickle::math::Vector<3, float> position;
};

#endif