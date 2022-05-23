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

    virtual float getIntensity(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal, pickle::math::Vector<3, float> view, float shininess) const override
    {
        float diffuse = std::clamp(dot(-direction, normal) * maxIntensity, 0.0f, 1.0f);
        pickle::math::Vector<3, float> viewDirection = normalize(point - view);
        pickle::math::Vector<3, float> reflectDirection = reflect(direction, normal);
        float specular = maxIntensity * std::pow(std::clamp(dot(-viewDirection, reflectDirection), 0.0f, 1.0f), shininess);

        return diffuse + specular;
    }

private:
    pickle::math::Vector<3, float> direction;
};

#endif