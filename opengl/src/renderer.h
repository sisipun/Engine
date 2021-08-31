#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL.h>

#include "scene/scene.h"

class Renderer
{
public:
    Renderer(SDL_Window *window);
    Renderer(const Renderer &renderer) = delete;
    Renderer &operator=(const Renderer &renderer) = delete;
    ~Renderer();

    void draw(const Scene &scene) const;

private:
    SDL_GLContext context;
    SDL_Window *window;
};

#endif