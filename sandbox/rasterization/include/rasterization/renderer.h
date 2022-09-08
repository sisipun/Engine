#ifndef RASTERIZATION_RENDERER_H
#define RASTERIZATION_RENDERER_H

#include <vector>
#include <SDL.h>

#include <rasterization/model_instance.h>
#include <rasterization/camera.h>
#include <pickle/math.h>

class Renderer
{
public:
    Renderer(float screenWidth,
             float screenHeight,
             float viewportWidth,
             float viewportHeight,
             float distanceToViewport,
             float maxDistance,
             Camera camera,
             pickle::math::Vector<3, float> lightDirection);

    void drawPoint(pickle::math::Vector<6, float> point);

    void drawLine(pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1);

    void drawWireTriangle(pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2);

    void drawTriangle(pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2);

    void drawModelInstance(const ModelInstance &instance);

    void present(SDL_Renderer *renderer);

    pickle::math::Vector<6, float> transformVertex(const pickle::math::Vector<6, float> &vertex, const pickle::math::Matrix<4, 4, float> &transform);

    pickle::math::Vector<6, float> viewportToScreen(const pickle::math::Vector<6, float> &vertex);

    bool isClipped(const pickle::math::Vector<6, float> &vertex) const;

private:
    std::vector<pickle::math::Vector<6, float>>
    interpolate(float a0, pickle::math::Vector<6, float> p0, float a1, pickle::math::Vector<6, float> p1);

private:
    float screenWidth;
    float screenHeight;
    float viewportWidth;
    float viewportHeight;
    float distanceToViewport;
    float maxDistance;
    Camera camera;
    pickle::math::Vector<3, float> lightDirection;
    pickle::math::Matrix<4, 4, float> projection;
    std::vector<pickle::math::Vector<6, float>> buffer;
};

#endif