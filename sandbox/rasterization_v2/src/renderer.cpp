#include <rasterization/renderer.h>

#include <iostream>

Renderer::Renderer(float width, float height) : width(width), height(height)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, pickle::math::Vector<2, float> point, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {static_cast<int>(point.data[0]), static_cast<int>(point.data[1]), 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end, Color color)
{
    bool swapped = false;
    if (std::abs(end.data[0] - start.data[0]) < std::abs(end.data[1] - start.data[1]))
    {
        std::swap(start.data[0], start.data[1]);
        std::swap(end.data[0], end.data[1]);
        swapped = true;
    }
    if (start.data[0] > end.data[0])
    {
        std::swap(start, end);
    }

    std::vector<float> line = interpolate(start.data[0], start.data[1], end.data[0], end.data[1]);
    for (float x = start.data[0]; x < end.data[0]; x++)
    {
        int index = x - start.data[0];
        if (swapped)
        {
            drawPoint(renderer, pickle::math::Vector<2, float>({line[index], x}), color);
        }
        else
        {
            drawPoint(renderer, pickle::math::Vector<2, float>({x, line[index]}), color);
        }
    }
}

void Renderer::drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<2, float> p1, pickle::math::Vector<2, float> p2, pickle::math::Vector<2, float> p3, Color color)
{
    if (p2.data[1] > p3.data[1])
    {
        std::swap(p2, p3);
    }
    if (p1.data[1] > p3.data[1])
    {
        std::swap(p1, p3);
    }
    if (p1.data[1] > p2.data[1])
    {
        std::swap(p1, p2);
    }

    std::vector<float> longSide = interpolate(p1.data[1], p1.data[0], p3.data[1], p3.data[0]);
    std::vector<float> shortSide;

    std::vector<float> shortSideFirtsPart = interpolate(p1.data[1], p1.data[0], p2.data[1], p2.data[0]);
    std::vector<float> shortSideSecondPart = interpolate(p2.data[1], p2.data[0], p3.data[1], p3.data[0]);

    shortSide.insert(shortSide.end(), shortSideFirtsPart.begin(), shortSideFirtsPart.end());
    shortSide.pop_back();
    shortSide.insert(shortSide.end(), shortSideSecondPart.begin(), shortSideSecondPart.end());

    for (float y = p1.data[1]; y < p3.data[1]; y++)
    {
        int index = y - p1.data[1];
        drawLine(renderer, pickle::math::Vector<2, float>({shortSide[index], y}), pickle::math::Vector<2, float>({longSide[index], y}), color);
    }
}

std::vector<float> Renderer::interpolate(float x0, float y0, float x1, float y1)
{
    std::vector<float> values;
    values.push_back(y0);
    if (x0 == x1)
    {
        return values;
    }

    float a = (y1 - y0) / (x1 - x0);
    float y = y0;
    for (float x = x0; x < x1; x++)
    {
        y += a;
        values.push_back(y);
    }

    return values;
}