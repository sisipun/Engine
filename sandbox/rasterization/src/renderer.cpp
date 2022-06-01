#include <rasterization/renderer.h>

Renderer::Renderer(float width, float height) : width(width), height(height)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, int x, int y, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, int> start, pickle::math::Vector<2, int> end, Color color)
{
    bool swapped = false;
    if (std::abs(end.data[1] - start.data[1]) > std::abs(end.data[0] - start.data[0]))
    {
        std::swap(start.data[0], start.data[1]);
        std::swap(end.data[0], end.data[1]);
        swapped = true;
    }
    if (start.data[0] > end.data[0])
    {
        std::swap(start, end);
    }
    float a = float(end.data[1] - start.data[1]) / float(end.data[0] - start.data[0]);
    float b = start.data[1] - a * start.data[0];
    float y = start.data[1];
    for (int x = start.data[0]; x < end.data[0]; x++)
    {
        y += a;
        if (swapped)
        {
            drawPoint(renderer, y, x, color);
        }
        else
        {
            drawPoint(renderer, x, y, color);
        }
    }
}

void Renderer::drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<2, int> p1, pickle::math::Vector<2, int> p2, pickle::math::Vector<2, int> p3, Color color)
{
    drawLine(renderer, p1, p2, color);
    drawLine(renderer, p2, p3, color);
    drawLine(renderer, p3, p1, color);
}