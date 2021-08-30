#include <iostream>

#include <SDL.h>

#include "window.h"

Window::Window(int screenWidth, int screenHeight) : screenWidth(screenWidth),
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

    SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        // Todo use logger
        std::cout << "Can't create window" << std::endl;
    }

    renderer = std::make_unique<Renderer>(window);
}

Window::~Window()
{
    SDL_Quit();
}