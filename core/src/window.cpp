#include <pickle/window.h>

#include <iostream>

#include <SDL.h>

#include <pickle/opengl_renderer.h>

namespace pickle
{
    Window::Window(int width, int height)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            // Todo use logger
            std::cout << "Can't load SDL module" << std::endl;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
        if (window == nullptr)
        {
            // Todo use logger
            std::cout << "Can't create window" << std::endl;
        }

        renderer = std::make_unique<OpenGLRenderer>(window);
    }

    Window::~Window()
    {
        SDL_Quit();
    }

    Renderer &Window::getRenderer() const
    {
        return *renderer;
    }

    bool Window::isClosed() const
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                return true;
            }
        }

        return false;
    }
}