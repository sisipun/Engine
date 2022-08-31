#include <rasterization/renderer.h>

#include <iostream>

Renderer::Renderer(float width, float height) : width(width), height(height)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, pickle::math::Vector<5, float> point)
{
    SDL_SetRenderDrawColor(renderer, point.data[2] * 0xFF, point.data[3] * 0xFF, point.data[4] * 0xFF, 0xFF);
    SDL_Rect rect = {static_cast<int>(point.data[0]), static_cast<int>(point.data[1]), 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<5, float> p0, pickle::math::Vector<5, float> p1)
{
    if (p0.data[0] > p1.data[0])
    {
        std::swap(p0, p1);
    }

    int aIndex = std::abs(p1.data[0] - p0.data[0]) < std::abs(p1.data[1] - p0.data[1]) ? 1 : 0;
    float a0 = p0.data[aIndex];
    float a1 = p1.data[aIndex];

    std::vector<pickle::math::Vector<5, float>> line = interpolate(a0, p0, a1, p1);
    for (const pickle::math::Vector<5, float> &point : line)
    {
        drawPoint(renderer, point);
    }
}

void Renderer::drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<5, float> p0, pickle::math::Vector<5, float> p1, pickle::math::Vector<5, float> p2)
{
    if (p1.data[1] > p2.data[1])
    {
        std::swap(p1, p2);
    }
    if (p0.data[1] > p2.data[1])
    {
        std::swap(p0, p2);
    }
    if (p0.data[1] > p1.data[1])
    {
        std::swap(p0, p1);
    }

    std::vector<pickle::math::Vector<5, float>> longSide = interpolate(p0.data[1], p0, p2.data[1], p2);
    std::vector<pickle::math::Vector<5, float>> shortSide;

    std::vector<pickle::math::Vector<5, float>> shortSideFirtsPart = interpolate(p0.data[1], p0, p1.data[1], p1);
    std::vector<pickle::math::Vector<5, float>> shortSideSecondPart = interpolate(p1.data[1], p1, p2.data[1], p2);

    shortSide.insert(shortSide.end(), shortSideFirtsPart.begin(), shortSideFirtsPart.end());
    shortSide.pop_back();
    shortSide.insert(shortSide.end(), shortSideSecondPart.begin(), shortSideSecondPart.end());

    for (float y = p0.data[1]; y < p2.data[1]; y++)
    {
        int index = y - p0.data[1];
        drawLine(renderer, shortSide[index], longSide[index]);
    }
}

std::vector<pickle::math::Vector<5, float>> Renderer::interpolate(float a0, pickle::math::Vector<5, float> p0, float a1, pickle::math::Vector<5, float> p1)
{
    std::vector<pickle::math::Vector<5, float>> values;
    values.push_back(p0);
    if (a0 == a1)
    {
        return values;
    }

    pickle::math::Vector<5, float> p = p0;
    for (float a = a0; a < a1; a++)
    {
        for (int i = 0; i < p.size(); i++)
        {
            p.data[i] += (p1.data[i] - p0.data[i]) / (a1 - a0);
        }
        values.push_back(p);
    }

    return values;
}