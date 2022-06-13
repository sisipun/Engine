#include <rasterization/renderer.h>

Renderer::Renderer(float width, float height) : width(width), height(height), widthStep(2.0f/width), heightStep(2.0f/height)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, float x, float y, Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {
        static_cast<int>(((x + 1.0f) / 2.0f) * width), 
        static_cast<int>(((-y + 1.0f) / 2.0f) * height), 
        1, 
        1};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end, Color color)
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

    std::unordered_map<float, float> sequence = interpolate(start.data[0], start.data[1], end.data[0], end.data[1]);
    for (float x = start.data[0]; x < end.data[0]; x+=widthStep)
    {
        float y = sequence[x];
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

void Renderer::drawTriangle(
    SDL_Renderer *renderer, 
    pickle::math::Vector<2, float> p1, 
    float h1,
    pickle::math::Vector<2, float> p2, 
    float h2,
    pickle::math::Vector<2, float> p3, 
    float h3,
    Color color
)
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

    std::unordered_map<float, float> longSide = interpolate(p3.data[1], p3.data[0], p1.data[1], p1.data[0]);
    std::unordered_map<float, float> topSide = interpolate(p2.data[1], p2.data[0], p1.data[1], p1.data[0]);
    std::unordered_map<float, float> bottomSide = interpolate(p3.data[1], p3.data[0], p2.data[1], p2.data[0]);

    std::unordered_map<float, float> longSideH = interpolate(p3.data[1], h3, p1.data[1], h1);
    std::unordered_map<float, float> topSideH = interpolate(p2.data[1], h2, p1.data[1], h1);
    std::unordered_map<float, float> bottomSideH = interpolate(p3.data[1], h3, p2.data[1], h2);

    for (float y = p3.data[1]; y < p1.data[1]; y+=heightStep)
    {
        float leftX = longSide[y];
        float rightX = y > p2.data[1] 
            ? topSide[y]
            : bottomSide[y];
        
        float leftH = longSideH[y];
        float rightH = y > p2.data[1] 
            ? topSideH[y]
            : bottomSideH[y];
        
        if (leftX > rightX)
        {
            std::swap(leftX, rightX);
            std::swap(leftH, rightH);
        }

        std::unordered_map<float, float> hValues = interpolate(leftX, leftH, rightX, rightH);
        for (float x = leftX; x < rightX; x+=widthStep) 
        {
            drawPoint(renderer, x, y, color * hValues[x]);
        }
    }
}

std::unordered_map<float, float> Renderer::interpolate(float x1, float y1, float x2, float y2)
{
    std::unordered_map<float, float> values;
    if (x1 == x2)
    {
        values.insert(std::pair<float, float>(x1, y1));
        return values;
    }
    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    float a = (y2 - y1) * heightStep / (x2 - x1);
    float b = y1 - a * x1;
    float y = y1;

    for (float x = x1; x < x2; x+=widthStep)
    {
        y += a;
        values.insert(std::pair<float, float>(x, y));
    }

    return values;
}