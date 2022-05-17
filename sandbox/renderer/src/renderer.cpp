#include <pickle/renderer.h>

#include <iostream>
#include <cmath>

pickle::renderer::Renderer::Renderer(SDL_Renderer *renderer, int width, int height) : renderer(renderer), width(width), height(height), depth(256)
{
    buffer = new Color[width * height];
    zBuffer = new int[width * height];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            buffer[i * width + j] = {0, 0, 0, 0};
            zBuffer[i * width + j] = depth;
        }
    }
}

pickle::renderer::Renderer::~Renderer()
{
    delete[] buffer;
    delete[] zBuffer;
}

void pickle::renderer::Renderer::drawPoint(math::Vector<3, float> p, Color color)
{
    int x = static_cast<int>((p.data[0] + 1) / 2 * (width - 1));
    int y = static_cast<int>((-p.data[1] + 1) / 2 * (height - 1));
    int z = static_cast<int>((-p.data[2] + 1) / 2 * (depth - 1));

    if (x >= 0 && x < width && y >= 0 && y < height && z > 0 && z < depth && zBuffer[x * width + y] > z)
    {
        zBuffer[x * width + y] = z;
        buffer[x * width + y] = color;
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

    float stepX = 1.0 / width;
    float stepY = 1.0 / height;

    for (float y = p3.data[1]; y < p1.data[1]; y += stepY)
    {
        bool firstHalf = y < p2.data[1];

        float leftT = (y - p3.data[1]) / (p1.data[1] - p3.data[1]);
        float rightT = firstHalf
                           ? (y - p3.data[1]) / (p2.data[1] - p3.data[1])
                           : (y - p2.data[1]) / (p1.data[1] - p2.data[1]);

        math::Vector<3, float> left = p3 + (p1 - p3) * leftT;
        math::Vector<3, float> right = firstHalf
                                           ? p3 + (p2 - p3) * rightT
                                           : p2 + (p1 - p2) * rightT;

        if (left.data[0] > right.data[0])
        {
            std::swap(left, right);
        }
        for (float x = left.data[0]; x < right.data[0]; x += stepX)
        {
            float t = (x - left.data[0]) / (right.data[0] - left.data[0]);
            math::Vector<3, float> current = left + (right - left) * t;
            drawPoint(current, {color.r, color.g, color.b, color.a});
        }
    }
}

void pickle::renderer::Renderer::drawTriangle(
    math::Vector<3, float> p1,
    math::Vector<3, float> tc1,
    math::Vector<3, float> p2,
    math::Vector<3, float> tc2,
    math::Vector<3, float> p3,
    math::Vector<3, float> tc3,
    float intensity,
    const Texture &texture)
{
    if (p1.data[1] < p2.data[1])
    {
        std::swap(p1, p2);
        std::swap(tc1, tc2);
    }
    if (p1.data[1] < p3.data[1])
    {
        std::swap(p1, p3);
        std::swap(tc1, tc3);
    }
    if (p2.data[1] < p3.data[1])
    {
        std::swap(p2, p3);
        std::swap(tc2, tc3);
    }

    float stepX = 1.0 / width;
    float stepY = 1.0 / height;

    for (float y = p3.data[1]; y < p1.data[1]; y += stepY)
    {
        bool firstHalf = y < p2.data[1];

        float leftT = (y - p3.data[1]) / (p1.data[1] - p3.data[1]);
        float rightT = firstHalf
                           ? (y - p3.data[1]) / (p2.data[1] - p3.data[1])
                           : (y - p2.data[1]) / (p1.data[1] - p2.data[1]);

        math::Vector<3, float> left = p3 + (p1 - p3) * leftT;
        math::Vector<3, float> leftTc = tc3 + (tc1 - tc3) * leftT;
        math::Vector<3, float> right = firstHalf
                                           ? p3 + (p2 - p3) * rightT
                                           : p2 + (p1 - p2) * rightT;
        math::Vector<3, float> rightTc = firstHalf
                                             ? tc3 + (tc2 - tc3) * rightT
                                             : tc2 + (tc1 - tc2) * rightT;

        if (left.data[0] > right.data[0])
        {
            std::swap(left, right);
        }
        for (float x = left.data[0]; x < right.data[0]; x += stepX)
        {
            float t = (x - left.data[0]) / (right.data[0] - left.data[0]);
            math::Vector<3, float> current = left + (right - left) * t;
            math::Vector<3, float> currentTc = leftTc + (rightTc - leftTc) * t;
            Color pixel = texture.getPixel(currentTc.data[0], currentTc.data[1]);
            drawPoint(current, pixel * intensity);
        }
    }
}

void pickle::renderer::Renderer::present()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Color color = buffer[i * width + j];
            if (color.a > 0)
            {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_Rect rect = {i, j, 1, 1};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}