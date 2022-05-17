#include <cmath>

#include "raytracing.h"
#include "geometry.h"

bool Sphere::ray_intersect(const Vec3f origin, const Vec3f direction, float &distance) const
{
    Vec3f L = center - origin;
    float tca = L * direction;
    float d2 = L * L - tca * tca;
    if (d2 > radius * radius)
        return false;

    float thc = radius * radius - d2;
    distance = tca - thc;
    if (distance < 0)
        distance = tca + thc;
    if (distance < 0)
        return false;
    return true;
}

Vec3f cast_ray(const Vec3f origin, const Vec3f destination, const std::vector<Sphere> &spheres)
{
    float distance = 0;
    for (Sphere shpere : spheres)
    {
        if (shpere.ray_intersect(origin, destination, distance))
        {
            return Vec3f(0x66, 0x66, 0x66);
        }
    }

    return Vec3f(0x22, 0xBB, 0xCC);
}

void Raytracing::render(SDL_Renderer *renderer, Vec3f position, const std::vector<Sphere> &spheres, int width, int height, int fov)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
            float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
            Vec3f direction = Vec3f(x, y, -1).normalize();
            Vec3f color = cast_ray(position, direction, spheres);
            SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 0xFF);
            SDL_Rect rect = {
                int(i),
                int(j),
                int(1),
                int(1)};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}