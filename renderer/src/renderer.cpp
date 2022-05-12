#include <pickle/renderer.h>

#include <iostream>
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

void pickle::renderer::Renderer::drawTriangle(math::Vector<3, float> p1, math::Vector<3, float> p2, math::Vector<3, float> p3, Color color)
{
    if (p1.data[1] < p2.data[1])
    {
        std::swap(p1, p2);
    }
    if (p1.data[1] < p3.data[1])
    {
        std::swap(p1, p3);
    }
    if (p2.data[1] < p3.data[1])
    {
        std::swap(p2, p3);
    }

    float stepX = 1 / width;
    float stepY = 1 / height;

    float fullHeight = p1.data[1] - p3.data[1];

    float firstHalfHeight = p2.data[1] - p3.data[1];
    for (float y = p3.data[1]; y < p2.data[1]; y += stepY)
    {
        float leftT = (y - p3.data[1]) / fullHeight;
        float rightT = (y - p3.data[1]) / firstHalfHeight;

        math::Vector<3, float> left = p3 + (p1 - p3) * leftT;
        math::Vector<3, float> right = p3 + (p2 - p3) * rightT;

        if (left.data[0] > right.data[0])
        {
            std::swap(left, right);
        }
        for (float x = left.data[0]; x < right.data[0]; x += stepX)
        {
            drawPoint(x, y, {color.r / 2.0f, color.g / 2.0f, color.b / 2.0f, color.a});
        }
    }

    float secondHalfHeight = p1.data[1] - p2.data[1];
    for (float y = p2.data[1]; y < p1.data[1]; y += stepY)
    {
        float leftT = (y - p3.data[1]) / fullHeight;
        float rightT = (y - p2.data[1]) / secondHalfHeight;

        math::Vector<3, float> left = p3 + (p1 - p3) * leftT;
        math::Vector<3, float> right = p2 + (p1 - p2) * rightT;

        if (left.data[0] > right.data[0])
        {
            std::swap(left, right);
        }
        for (float x = left.data[0]; x < right.data[0]; x += stepX)
        {
            drawPoint(x, y, {color.r / 2.0f, color.g / 2.0f, color.b / 2.0f, color.a});
        }
    }
}