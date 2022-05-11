#include <pickle/renderer.h>

#include <cmath>

pickle::renderer::Renderer::Renderer(SDL_Renderer *renderer, float width, float height) : renderer(renderer), width(width), height(height)
{
}

void pickle::renderer::Renderer::drawPoint(float x, float y, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r * 0xFF, color.g * 0xFF, color.b * 0xFF, color.a * 0xFF);

    SDL_Rect rect = {static_cast<int>((x + 1) / 2 * width), static_cast<int>((-y + 1) / 2 * height), 1, 1};

    SDL_RenderFillRect(renderer, &rect);
}

void pickle::renderer::Renderer::drawLine(float x1, float y1, float x2, float y2, Color color)
{
    bool steep = false;
    if (std::abs(x2 - x1) < std::abs(y2 - y1))
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }

    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    float stepX = 1 / width;
    float stepY = 1 / height;

    float dx = std::abs(x2 - x1);
    float dy = std::abs(y2 - y1);
    float derror = dy;
    float error = 0;
    float directionY = y2 > y1 ? stepY : -stepY;

    float y = y1;
    for (float x = x1; x <= x2; x += stepX)
    {
        error += derror;

        if (error > dx)
        {
            y += directionY;
            error -= dx;
        }

        if (steep)
        {
            drawPoint(y, x, color);
        }
        else
        {
            drawPoint(x, y, color);
        }
    }
}

void pickle::renderer::Renderer::drawTriangle(math::Vector<2, float> p1, math::Vector<2, float> p2, math::Vector<2, float> p3, Color color)
{
    drawLine(p1.data[0], p1.data[1], p2.data[0], p2.data[1], color);
    drawLine(p2.data[0], p2.data[1], p3.data[0], p3.data[1], color);
    drawLine(p3.data[0], p3.data[1], p1.data[0], p1.data[1], color);
}