#include <rasterization/renderer.h>

Renderer::Renderer(float width, float height) : width(width), height(height)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, pickle::math::Vector<2, float> point, Color color)
{
    // TODO make drawPoint function
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end, Color color)
{
    // TODO make drawLine function
}

std::unordered_map<float, float> Renderer::interpolate(float x1, float y1, float x2, float y2)
{
    std::unordered_map<float, float> values;
    // TODO make interpolate function
    return values;
}