#ifndef RASTERIZATION_RENDERER_H
#define RASTERIZATION_RENDERER_H

#include <vector>
#include <SDL.h>

#include <pickle/math.h>

#include <rasterization/color.h>

class Renderer
{
public:
    Renderer(float width, float height);

    void drawPoint(SDL_Renderer *renderer, pickle::math::Vector<2, float> point, Color color);

    void drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end, Color color);

    void drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<2, float> p1, pickle::math::Vector<2, float> p2, pickle::math::Vector<2, float> p3, Color color);

private:
    std::vector<float> interpolate(float x0, float y0, float x1, float y1);

private:
    float width;
    float height;
};

#endif