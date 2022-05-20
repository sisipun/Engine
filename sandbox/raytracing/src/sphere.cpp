#include <raytracing/sphere.h>

#include <iostream>
#include <cmath>

Sphere::Sphere(pickle::math::Vector<3, float> center, float radius, Color color) : Shape(color), center(center), radius(radius)
{
}

pickle::math::Vector<2, float> Sphere::intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray) const
{
    pickle::math::Vector<3, float> rayDirection = ray - origin;
    pickle::math::Vector<3, float> originToCenter = origin - center;

    float k1 = dot(rayDirection, rayDirection);
    float k2 = 2.0f * dot(rayDirection, originToCenter);
    float k3 = dot(originToCenter, originToCenter) - radius * radius;

    float descriminant = k2 * k2 - 4 * k1 * k3;
    if (descriminant < 0.0)
    {
        return pickle::math::Vector<2, float>({-1.0f, -1.0f});
    }

    return pickle::math::Vector<2, float>({(-k2 - std::sqrt(descriminant)) / (2 * k1),
                                           (-k2 + std::sqrt(descriminant)) / (2 * k1)});
}