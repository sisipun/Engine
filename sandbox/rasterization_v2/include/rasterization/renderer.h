#ifndef RASTERIZATION_RENDERER_H
#define RASTERIZATION_RENDERER_H

#include <vector>
#include <SDL.h>

#include <pickle/math.h>

class Renderer
{
public:
    Renderer(float screenWidth, float screenHeight, float viewportWidth, float viewportHeight, float distanceToViewport);

    void drawPoint(SDL_Renderer *renderer, pickle::math::Vector<6, float> point);

    void drawLine(SDL_Renderer *renderer, pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1);

    void drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<6, float> p0, pickle::math::Vector<6, float> p1, pickle::math::Vector<6, float> p2);

    pickle::math::Vector<6, float> projectVertex(pickle::math::Vector<6, float> vertex);

    pickle::math::Vector<6, float> viewportToScreen(pickle::math::Vector<6, float> vertex);

private:
    std::vector<pickle::math::Vector<6, float>> interpolate(float a0, pickle::math::Vector<6, float> p0, float a1, pickle::math::Vector<6, float> p1);

private:
    float screenWidth;
    float screenHeight;
    float viewportWidth;
    float viewportHeight;
    float distanceToViewport;
};

#endif