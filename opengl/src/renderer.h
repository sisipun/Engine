#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL.h>

#include "scene/scene.h"

class Renderer
{
public:
    Renderer(int screenWidth, int screeHeight);

    ~Renderer();

    void render(const Scene &scene) const;

private:
    int screenWidth;
    int screenHeight;

    SDL_GLContext context;
    SDL_Event event;
    SDL_Window *window;
};

#endif