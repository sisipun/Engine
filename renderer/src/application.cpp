#include <pickle/application.h>

#include <SDL.h>

namespace pickle
{
    Application::Application() : window(800, 600)
    {
    }

    Application::~Application()
    {
    }

    void Application::start()
    {
        SDL_Event event;

        bool quit = false;
        while (!quit)
        {
            window.getRenderer().render();
            if (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
    }
}