#include <rasterization/renderer.h>

#include <iostream>

Renderer::Renderer(float width, float height) : width(width), height(height)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, pickle::math::Vector<2, float> point, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {
        static_cast<int>(point.data[0]),
        static_cast<int>(point.data[1]),
        1,
        1};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end, Color color)
{
    std::vector<pickle::math::Vector<2, float>> line = interpolate(start, end);
    std::cout << "Draw" << std::endl;
    for (const pickle::math::Vector<2, float> &point : line)
    {
        std::cout << "Point - (" << point.data[0] << "-" << point.data[1] << ")" << std::endl;
        drawPoint(renderer, point, color);
    }
}

std::vector<pickle::math::Vector<2, float>> Renderer::interpolate(pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end)
{
    std::vector<pickle::math::Vector<2, float>> values;
    bool swapped = false;
    if (std::abs(end.data[0] - start.data[0]) < std::abs(end.data[1] - start.data[1]))
    {
        std::swap(start.data[0], start.data[1]);
        std::swap(end.data[0], end.data[1]);
        swapped = true;
    }
    if (start.data[0] == end.data[0])
    {
        return values;
    }
    if (start.data[0] > end.data[0])
    {
        std::swap(start, end);
    }

    float a = (end.data[1] - start.data[1]) / (end.data[0] - start.data[0]);
    float y = start.data[1];
    for (float x = start.data[0]; x < end.data[0]; x++)
    {
        y += a;
        if (swapped)
        {
            values.push_back(pickle::math::Vector({y, x}));
        }
        else
        {
            values.push_back(pickle::math::Vector({x, y}));
        }
    }

    return values;
}