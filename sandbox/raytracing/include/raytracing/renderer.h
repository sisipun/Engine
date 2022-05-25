#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

#include <vector>

#include <SDL.h>
#include <pickle/math.h>

#include "shape.h"
#include "light.h"
#include "color.h"

class Renderer
{
public:
    Renderer(float screenWidth, float screenHeight, Color background, int maxDepth);
    Renderer(const Renderer &renderer) = delete;
    Renderer &operator=(const Renderer &renderer) = delete;

    void setViewport(float viewportWidth, float viewportHeight, float viewportDistance);

    void render(SDL_Renderer *renderer,
                const std::vector<std::unique_ptr<Shape> > &shapes,
                const std::vector<std::unique_ptr<Light> > &lights) const;

private:
    pickle::math::Vector<3, float> screenToViewport(float x, float y) const;

    Color traceRay(pickle::math::Vector<3, float> origin,
                   pickle::math::Vector<3, float> ray,
                   float minDist,
                   float maxDist,
                   int depth,
                   const std::vector<std::unique_ptr<Shape> > &shapes,
                   const std::vector<std::unique_ptr<Light> > &lights) const;

    Color calculateLight(
        pickle::math::Vector<3, float> point,
        pickle::math::Vector<3, float> normal,
        pickle::math::Vector<3, float> view,
        Color color,
        float shininess,
        const std::vector<std::unique_ptr<Shape> > &shapes,
        const std::vector<std::unique_ptr<Light> > &lights) const;

    void drawPoint(SDL_Renderer *renderer, float x, float y, Color color) const;

    Color background;
    float screenWidth;
    float screenHeight;
    float viewportWidth;
    float viewportHeight;
    float viewportDistance;
    int maxDepth;
};

#endif