#include <raytracing/renderer.h>

#include <algorithm>
#include <limits>

Renderer::Renderer(float screenWidth, float screenHeight, Color background) : screenWidth(screenWidth), screenHeight(screenHeight), viewportWidth(screenWidth), viewportHeight(screenHeight), viewportDistance(1.0f), background(background)
{
}

void Renderer::render(SDL_Renderer *renderer, const std::vector<std::unique_ptr<Shape> > &shapes, const std::vector<std::unique_ptr<Light> > &lights) const
{
    pickle::math::Vector<3, float> origin({0.0f, 0.0f, 0.0f});
    for (float x = -screenWidth / 2; x < screenWidth / 2; x++)
    {
        for (float y = -screenHeight / 2; y < screenHeight / 2; y++)
        {
            pickle::math::Vector<3, float> ray = screenToViewport(x, y);
            Color color = traceRay(origin, ray, 1.0f, std::numeric_limits<float>::max(), shapes, lights);
            drawPoint(renderer, x, y, color);
        }
    }
}

void Renderer::setViewport(float viewportWidth, float viewportHeight, float viewportDistance)
{
    this->viewportWidth = viewportWidth;
    this->viewportHeight = viewportHeight;
    this->viewportDistance = viewportDistance;
}

pickle::math::Vector<3, float> Renderer::screenToViewport(float x, float y) const
{
    return pickle::math::Vector<3, float>({x * viewportWidth / screenWidth, y * viewportHeight / screenHeight, viewportDistance});
}

Color Renderer::traceRay(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray, float minDist, float maxDist, const std::vector<std::unique_ptr<Shape> > &shapes, const std::vector<std::unique_ptr<Light> > &lights) const
{
    if (shapes.empty())
    {
        return background;
    }

    float closestT = std::numeric_limits<float>::max();
    Shape *closestShape = nullptr;

    for (const std::unique_ptr<Shape> &shape : shapes)
    {
        pickle::math::Vector<2, float> t = shape->intersect(origin, ray - origin);
        if (t.data[0] > minDist && t.data[0] < maxDist && t.data[0] < closestT)
        {
            closestT = t.data[0];
            closestShape = shape.get();
        }
        if (t.data[1] > minDist && t.data[1] < maxDist && t.data[1] < closestT)
        {
            closestT = t.data[1];
            closestShape = shape.get();
        }
    }

    if (closestShape == nullptr)
    {
        return background;
    }

    pickle::math::Vector<3, float> point = origin + (ray * closestT);
    return calculateLight(point, closestShape->getNormal(point), origin, closestShape->getColor(), closestShape->getShininess(), shapes, lights);
}

Color Renderer::calculateLight(pickle::math::Vector<3, float> point, pickle::math::Vector<3, float> normal, pickle::math::Vector<3, float> view, Color color, float shininess, const std::vector<std::unique_ptr<Shape> > &shapes, const std::vector<std::unique_ptr<Light> > &lights) const
{
    float intensity = 0.0f;
    for (const std::unique_ptr<Light> &light : lights)
    {
        intensity += light->getIntensity(point, normal, view, shininess, shapes);
    }

    return color * std::clamp(intensity, 0.0f, 1.0f);
}

void Renderer::drawPoint(SDL_Renderer *renderer, float x, float y, Color color) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {static_cast<int>(x + (screenWidth / 2)), static_cast<int>(-y + (screenHeight / 2)), 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}
