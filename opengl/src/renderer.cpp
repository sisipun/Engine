#include "renderer.h"

#include <iostream>

#include <glad/glad.h>
#include <stbimage/stb_image.h>

Renderer::Renderer(int screenWidth, int screenHeight) : screenWidth(screenWidth),
                                                        screenHeight(screenHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Todo use logger
        std::cout << "Can't load SDL module" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        // Todo use logger
        std::cout << "Can't create window" << std::endl;
    }

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
    SDL_Quit();
}

void Renderer::draw(const Scene &scene) const
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.draw();

    SDL_GL_SwapWindow(window);
}