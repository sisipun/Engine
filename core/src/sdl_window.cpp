#include <pickle/sdl_window.h>

#include <SDL.h>

#include <pickle/logger.h>

pickle::SdlWindow::SdlWindow(int width, int height) : Window(width, height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR("Can't load SDL module");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        LOG_ERROR("Can't create window");
    }
}

pickle::SdlWindow::~SdlWindow()
{
    SDL_Quit();
}

SDL_Window* pickle::SdlWindow::getWindow() const
{
    return window;
}

void pickle::SdlWindow::update() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            closed = true;
            return;
        }
    }
}