#ifndef RAYTRACING_H
#define RAYTRACING_H

#include <vector>
#include <SDL.h>

#include "geometry.h"

struct Sphere
{
    Vec3f center;
    float radius;

    Sphere(const Vec3f center, const float radius) : center(center), radius(radius)
    {
    }

    bool ray_intersect(const Vec3f origin, const Vec3f direction, float &distance) const;
};

class Raytracing
{
public:
    void render(SDL_Renderer *renderer, Vec3f position, const std::vector<Sphere> &spheres, int width, int height, int fov);
};

#endif