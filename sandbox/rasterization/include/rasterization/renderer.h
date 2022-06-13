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

    void drawPoint(SDL_Renderer *renderer, float x, float y, Color color);

    void drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, float> start, pickle::math::Vector<2, float> end, Color color);

    void drawTriangle(SDL_Renderer *renderer, pickle::math::Vector<2, float> p1, float h1, pickle::math::Vector<2, float> p2, float h2, pickle::math::Vector<2, float> p3, float h3, Color color);

private:
    std::unordered_map<float, float> interpolate(float x1, float y1, float x2, float y2);

private:
    float width;
    float height;
    float widthStep;
    float heightStep;
};

#endif