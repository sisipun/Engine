#ifndef RASTERIZATION_RENDERER_H
#define RASTERIZATION_RENDERER_H

#include <unordered_map>
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
    std::unordered_map<float, float> interpolate(float x1, float y1, float x2, float y2);

private:
    float width;
    float height;
};

#endif