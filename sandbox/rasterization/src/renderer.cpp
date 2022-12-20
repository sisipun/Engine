#include <rasterization/renderer.h>

Renderer::Renderer(
    float screenWidth,
    float screenHeight,
    float viewportWidth,
    float viewportHeight,
    float distanceToViewport,
    float maxDistance,
    Camera camera,
    pickle::math::Vector<3, float> lightDirection)
    : screenWidth(screenWidth),
      screenHeight(screenHeight),
      viewportWidth(viewportWidth),
      viewportHeight(viewportHeight),
      distanceToViewport(distanceToViewport),
      maxDistance(maxDistance),
      camera(camera),
      lightDirection(normalize(lightDirection)),
      projection({distanceToViewport / viewportWidth, 0.0f, 0.0f, 0.0f,
                  0.0f, distanceToViewport / viewportHeight, 0.0f, 0.0f,
                  0.0f, 0.0f, 1 / (maxDistance - distanceToViewport), -distanceToViewport / (maxDistance - distanceToViewport),
                  0.0f, 0.0f, 1.0f, 0.0f})
{
    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            buffer.push_back(pickle::math::Vector<6, float>());
        }
    }
}

void Renderer::drawPoint(pickle::math::Vector<6, float> point)
{
    int x = point.data[0];
    int y = point.data[1];
    if (buffer[x * screenHeight + y].data[2] < point.data[2])
    {
        buffer[x * screenHeight + y] = point;
    }
}

void Renderer::drawLine(pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1)
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
        drawPoint(point);
    }
}

void Renderer::drawWireTriangle(pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2)
{
    drawLine(p0, p1);
    drawLine(p1, p2);
    drawLine(p2, p0);
}

void Renderer::drawTriangle(pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2)
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
        drawLine(shortSide[index], longSide[index]);
    }
}

void Renderer::drawModelInstance(const ModelInstance &instance)
{
    std::vector<pickle::math::Vector<6, float>> projectedVertices;
    for (const pickle::math::Vector<6, float> &vertex : instance.model.vertices)
    {
        projectedVertices.push_back(transformVertex(vertex, instance.transform));
    }

    for (const pickle::math::Vector<3, int> &triangle : instance.model.triangles)
    {
        pickle::math::Vector<6, float> v0 = projectedVertices[triangle.data[0]];
        pickle::math::Vector<6, float> v1 = projectedVertices[triangle.data[1]];
        pickle::math::Vector<6, float> v2 = projectedVertices[triangle.data[2]];

        if (isClipped(v0) && isClipped(v1) && isClipped(v2))
        {
            continue;
        }

        pickle::math::Vector<3, float> v0Pos = v0.cutDimension<3, 3>();
        pickle::math::Vector<3, float> v1Pos = v1.cutDimension<3, 3>();
        pickle::math::Vector<3, float> v2Pos = v2.cutDimension<3, 3>();
        pickle::math::Vector<3, float> norm = normalize(cross(v1Pos - v0Pos, v2Pos - v0Pos));
        pickle::math::Vector<3, float> view = -camera.getViewDirection();

        if (dot(norm, view) <= 0)
        {
            continue;
        }

        float ambientLightPower = 0.2f;
        float diffuseLightPower = std::max(dot(norm, -lightDirection), 0.0f);
        float lightPower = ambientLightPower + diffuseLightPower;

        v0 = v0.replace<3, 3>(v0.cutDimension<0, 3>() * lightPower);
        v1 = v1.replace<3, 3>(v1.cutDimension<0, 3>() * lightPower);
        v2 = v2.replace<3, 3>(v2.cutDimension<0, 3>() * lightPower);

        drawTriangle(viewportToScreen(v0), viewportToScreen(v1), viewportToScreen(v2));
    }
}

void Renderer::present(SDL_Renderer *renderer)
{
    for (const pickle::math::Vector<6, float> &point : buffer)
    {
        SDL_SetRenderDrawColor(
            renderer,
            std::clamp(point.data[3], 0.0f, 1.0f) * 0xFF,
            std::clamp(point.data[4], 0.0f, 1.0f) * 0xFF,
            std::clamp(point.data[5], 0.0f, 1.0f) * 0xFF,
            0xFF);
        SDL_Rect rect = {static_cast<int>(point.data[0]), static_cast<int>(point.data[1]), 1, 1};
        SDL_RenderFillRect(renderer, &rect);
    }
}

pickle::math::Vector<6, float> Renderer::transformVertex(const pickle::math::Vector<6, float> &vertex, const pickle::math::Matrix<4, 4, float> &transform)
{
    pickle::math::Vector<6, float> transformedVertex(vertex.data);
    pickle::math::Vector<4, float> positionVertexPart = transformedVertex.cutDimension<3, 3>().addDimension<3>(1.0f);

    pickle::math::Matrix<4, 4, float> view = camera.getViewMatrix();
    pickle::math::Vector<4, float> transformedPositionVertexPart = projection * view * transform * positionVertexPart;

    transformedVertex.data[0] = transformedPositionVertexPart.data[0] / transformedPositionVertexPart.data[3];
    transformedVertex.data[1] = transformedPositionVertexPart.data[1] / transformedPositionVertexPart.data[3];
    transformedVertex.data[2] = transformedPositionVertexPart.data[2];

    return transformedVertex;
}

pickle::math::Vector<6, float> Renderer::viewportToScreen(const pickle::math::Vector<6, float> &vertex)
{
    pickle::math::Vector<6, float> screenVertex(vertex.data);
    float halfScreenWidth = screenWidth / 2.0f;
    float halfScreenHeight = screenHeight / 2.0f;

    screenVertex.data[0] = screenVertex.data[0] * halfScreenWidth / viewportWidth + halfScreenWidth;
    screenVertex.data[1] = -screenVertex.data[1] * halfScreenHeight / viewportHeight + halfScreenHeight;
    screenVertex.data[2] = 1.0f / screenVertex.data[2];
    return screenVertex;
}

bool Renderer::isClipped(const pickle::math::Vector<6, float> &vertex) const
{
    return vertex.data[0] < -viewportWidth || vertex.data[0] > viewportWidth || vertex.data[1] < -viewportHeight || vertex.data[1] > viewportHeight || vertex.data[2] < 0.0f || vertex.data[2] > 1.0f;
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
    for (int a = a0; a < a1; a++)
    {
        for (int i = 0; i < p.size(); i++)
        {
            p.data[i] += (p1.data[i] - p0.data[i]) / (a1 - a0);
        }
        values.push_back(p);
    }

    return values;
}