#ifndef RASTERIZATION_RENDERER_H
#define RASTERIZATION_RENDERER_H

#include <vector>
#include <SDL.h>

#include <pickle/math.h>

class Renderer
{
public:
    Renderer(float width, float height);

    void drawPoint(SDL_Renderer *renderer, pickle::math::Vector<5, float> point);

    void drawLine(SDL_Renderer *renderer, pickle::math::Vector<5, float> p0, pickle::math::Vector<5, float> p1);

    void drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<5, float> p0, pickle::math::Vector<5, float> p1, pickle::math::Vector<5, float> p2);

private:
    std::vector<pickle::math::Vector<5, float>> interpolate(float a0, pickle::math::Vector<5, float> p0, float a1, pickle::math::Vector<5, float> p1);

private:
    float width;
    float height;
};

#endif