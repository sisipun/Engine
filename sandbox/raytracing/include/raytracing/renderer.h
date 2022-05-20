#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include <vector>

#include <SDL.h>
#include <pickle/math.h>

#include "shape.h"
#include "color.h"

class Renderer
{
public:
    Renderer(float screenWidth, float screenHeight, Color background);

    void setViewport(float viewportWidth, float viewportHeight, float viewportDistance);

    void render(SDL_Renderer *renderer, const std::vector<std::unique_ptr<Shape> > &shapes) const;

private:
    pickle::math::Vector<3, float> screenToViewport(float x, float y) const;

    Color traceRay(pickle::math::Vector<3, float> origin, pickle::math::Vector<3, float> ray, float minDist, float maxDist, const std::vector<std::unique_ptr<Shape> > &shapes) const;

    void drawPoint(SDL_Renderer *renderer, float x, float y, Color color) const;

    Color background;
    float screenWidth;
    float screenHeight;
    float viewportWidth;
    float viewportHeight;
    float viewportDistance;
};

#endif