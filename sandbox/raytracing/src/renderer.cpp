#include <raytracing/renderer.h>

Renderer::Renderer(float screenWidth, float screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), viewportWidth(screenWidth), viewportHeight(screenHeight), viewportDistance(1.0f)
{
}

void Renderer::render(SDL_Renderer *renderer, const std::vector<std::unique_ptr<Shape> > &shapes)
{
    drawPoint(renderer, 0, 0, {0xFF, 0x00, 0x00, 0xFF});
}

void Renderer::viewport(float viewportWidth, float viewportHeight, float viewportDistance)
{
    this->viewportWidth = viewportWidth;
    this->viewportHeight = viewportHeight;
    this->viewportDistance = viewportDistance;
}

Color Renderer::traceRay(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray, float minDist, float maxDist)
{
    return {0xFF, 0xFF, 0xFF, 0xFF};
}

void Renderer::drawPoint(SDL_Renderer *renderer, float x, float y, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {static_cast<int>(x + (screenWidth / 2)), static_cast<int>(y + (screenHeight / 2)), 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}
