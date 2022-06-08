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

    std::vector<int> sequence = interpolate(start.data[0], start.data[1], end.data[0], end.data[1]);
    for (int x = start.data[0]; x < end.data[0]; x++)
    {
        int y = sequence[x - start.data[0]];
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

    std::vector<int> longSide = interpolate(p3.data[1], p3.data[0], p1.data[1], p1.data[0]);
    std::vector<int> topSide = interpolate(p2.data[1], p2.data[0], p1.data[1], p1.data[0]);
    std::vector<int> bottomSide = interpolate(p3.data[1], p3.data[0], p2.data[1], p2.data[0]);

    for (int y = p3.data[1]; y < p1.data[1]; y++)
    {
        int index = y - p3.data[1];
        int leftX = longSide[index];
        int rightX = y < topSide.size() 
            ? topSide[index] 
            : bottomSide[index - topSide.size() + 1];
        
        if (leftX > rightX)
        {
            std::swap(leftX, rightX);
        }

        for (int x = leftX; x < rightX; x++) 
        {
            drawPoint(renderer, x, y, color);
        }
    }
}

std::vector<int> Renderer::interpolate(int x1, int y1, int x2, int y2)
{
    std::vector<int> values;
    if (x1 == x2)
    {
        values.push_back(y1);
        return values;
    }
    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    float a = float(y2 - y1) / float(x2 - x1);
    float b = y1 - a * x1;
    float y = y1;

    for (int x = x1; x < x2; x++)
    {
        y += a;
        values.push_back(y);
    }

    return values;
}