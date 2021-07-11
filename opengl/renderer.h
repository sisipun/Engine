#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL.h>

#include "shader.h"
#include "camera.h"
#include "light.h"
#include "model.h"

class Renderer
{
public:
    Renderer(int screenWidth, int screeHeight);

    ~Renderer();

    void draw(std::vector<Model> models) const;

private:
    int screenWidth;
    int screeHeight;
    Shader shader;
    Camera camera;
    Light light;

    SDL_GLContext context;
    SDL_Window *window;
};

#endif