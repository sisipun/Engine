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

private:
    std::vector<pickle::math::Vector<2, float>> interpolate(pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end);

private:
    float width;
    float height;
};

#endif