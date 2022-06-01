#ifndef RASTERIZATION_RENDERER_H
#define RASTERIZATION_RENDERER_H

#include <SDL.h>

#include <pickle/math.h>

#include <rasterization/color.h>

class Renderer
{
public:
    Renderer(float width, float height);

    void drawPoint(SDL_Renderer *renderer, int x, int y, Color color);

    void drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, int> start, pickle::math::Vector<2, int> end, Color color);

    void drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<2, int> p1, pickle::math::Vector<2, int> p2, pickle::math::Vector<2, int> p3, Color color);

private:
    float width;
    float height;
};

#endif