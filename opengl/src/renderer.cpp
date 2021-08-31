#include "renderer.h"

#include <iostream>

#include <glad/glad.h>
#include <stbimage/stb_image.h>

Renderer::Renderer(SDL_Window *window) : window(window)
{
    context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        // Todo use logger
        std::cout << "Can't load glad module" << std::endl;
    }

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(context);
}

void Renderer::draw(const Scene &scene) const
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene.draw();
    SDL_GL_SwapWindow(window);
}