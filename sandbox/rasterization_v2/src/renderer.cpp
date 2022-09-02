#include <rasterization/renderer.h>

#include <iostream>

Renderer::Renderer(float screenWidth, float screenHeight, float viewportWidth, float viewportHeight, float distanceToViewport) : screenWidth(screenWidth), screenHeight(screenHeight), viewportWidth(viewportWidth), viewportHeight(viewportHeight), distanceToViewport(distanceToViewport)
{
}

void Renderer::drawPoint(SDL_Renderer *renderer, pickle::math::Vector<6, float> point)
{
    float x = (screenWidth / 2.0f) + point.data[0];
    float y = (screenHeight / 2.0f) - point.data[1];

    if (x < 0 || x > screenWidth || y < 0 || y > screenHeight)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, point.data[3] * 0xFF, point.data[4] * 0xFF, point.data[5] * 0xFF, 0xFF);
    SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawLine(SDL_Renderer *renderer, pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1)
{
    int aIndex = std::abs(p1.data[0] - p0.data[0]) < std::abs(p1.data[1] - p0.data[1]) ? 1 : 0;
    float a0 = p0.data[aIndex];
    float a1 = p1.data[aIndex];

    if (a0 > a1)
    {
        std::swap(a0, a1);
        std::swap(p0, p1);
    }

    std::vector<pickle::math::Vector<6, float>> line = interpolate(a0, p0, a1, p1);
    for (const pickle::math::Vector<6, float> &point : line)
    {
        drawPoint(renderer, point);
    }
}

void Renderer::drawWireTriangle(SDL_Renderer *renderer, pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2)
{
    drawLine(renderer, p0, p1);
    drawLine(renderer, p1, p2);
    drawLine(renderer, p2, p0);
}

void Renderer::drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2)
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

    std::vector<pickle::math::Vector<6, float>> longSide = interpolate(p0.data[1], p0, p2.data[1], p2);
    std::vector<pickle::math::Vector<6, float>> shortSide;

    std::vector<pickle::math::Vector<6, float>> shortSideFirtsPart = interpolate(p0.data[1], p0, p1.data[1], p1);
    std::vector<pickle::math::Vector<6, float>> shortSideSecondPart = interpolate(p1.data[1], p1, p2.data[1], p2);

    shortSide.insert(shortSide.end(), shortSideFirtsPart.begin(), shortSideFirtsPart.end());
    shortSide.pop_back();
    shortSide.insert(shortSide.end(), shortSideSecondPart.begin(), shortSideSecondPart.end());

    for (float y = p0.data[1]; y < p2.data[1]; y++)
    {
        int index = y - p0.data[1];
        drawLine(renderer, shortSide[index], longSide[index]);
    }
}

void Renderer::drawModelInstance(SDL_Renderer *renderer, const ModelInstance &instance)
{
    std::vector<pickle::math::Vector<6, float>> projectedVertices;
    for (const pickle::math::Vector<6, float> &vertex : instance.model.vertices)
    {
        projectedVertices.push_back(projectVertex(transformVertex(vertex, instance.transform)));
    }

    for (const pickle::math::Vector<3, int> &triangle : instance.model.triangles)
    {
        drawWireTriangle(renderer, projectedVertices[triangle.data[0]], projectedVertices[triangle.data[1]], projectedVertices[triangle.data[2]]);
    }
}

pickle::math::Vector<6, float> Renderer::transformVertex(pickle::math::Vector<6, float> vertex, const pickle::math::Matrix<4, 4, float> &transform)
{
    vertex.data[0] = vertex.data[0] + transform.data[0 * transform.columns() + 3];
    vertex.data[1] = vertex.data[1] + transform.data[1 * transform.columns() + 3];
    vertex.data[2] = vertex.data[2] + transform.data[2 * transform.columns() + 3];
    return vertex;
}

pickle::math::Vector<6, float> Renderer::projectVertex(pickle::math::Vector<6, float> vertex)
{
    vertex.data[0] = (vertex.data[0] * distanceToViewport) / vertex.data[2];
    vertex.data[1] = (vertex.data[1] * distanceToViewport) / vertex.data[2];
    return viewportToScreen(vertex);
}

pickle::math::Vector<6, float> Renderer::viewportToScreen(pickle::math::Vector<6, float> vertex)
{
    vertex.data[0] = (vertex.data[0] * screenWidth) / viewportWidth;
    vertex.data[1] = (vertex.data[1] * screenHeight) / viewportHeight;
    return vertex;
}

std::vector<pickle::math::Vector<6, float>> Renderer::interpolate(float a0, pickle::math::Vector<6, float> p0, float a1, pickle::math::Vector<6, float> p1)
{
    std::vector<pickle::math::Vector<6, float>> values;
    values.push_back(p0);
    if (a0 == a1)
    {
        return values;
    }

    pickle::math::Vector<6, float> p = p0;
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