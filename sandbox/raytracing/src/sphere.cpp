#include <raytracing/sphere.h>

Sphere::Sphere(pickle::math::Vector<3, float> center, float radius, Color color) : center(center), radius(radius), color(color)
{
}

pickle::math::Vector<2, float> Sphere::intersect(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray)
{
    return pickle::math::Vector<2, float>({0.0f, 0.0f});
}