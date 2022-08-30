#include <SDL.h>

#include <pickle/math.h>

#include <rasterization/renderer.h>

int main(int argc, char *argv[])
{
    const int width = 600;
    const int height = 600;
    const int fov = M_PI / 2;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        return -1;
    }

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr)
    {
        return -1;
    }

    SDL_Event *event = new SDL_Event();

    bool quit = false;

    Renderer renderer(width, height);

    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);

    // Render
    // renderer.drawLine(sdlRenderer, pickle::math::Vector({100.0f, 100.0f}), pickle::math::Vector({500.0f, 500.0f}), {0xFF, 0x00, 0x00, 0xFF});
    // renderer.drawLine(sdlRenderer, pickle::math::Vector({100.0f, 300.0f}), pickle::math::Vector({500.0f, 300.0f}), {0x00, 0xFF, 0x00, 0xFF});
    // renderer.drawLine(sdlRenderer, pickle::math::Vector({300.0f, 100.0f}), pickle::math::Vector({300.0f, 500.0f}), {0x00, 0x00, 0xFF, 0xFF});
    // renderer.drawLine(sdlRenderer, pickle::math::Vector({500.0f, 100.0f}), pickle::math::Vector({100.0f, 500.0f}), {0xFF, 0x00, 0xFF, 0xFF});
    renderer.drawTriangle(sdlRenderer, pickle::math::Vector({100.0f, 100.0f}), pickle::math::Vector({200.0f, 200.0f}), pickle::math::Vector({100.0f, 300.0f}), {0xFF, 0x00, 0x00, 0xFF});
    renderer.drawTriangle(sdlRenderer, pickle::math::Vector({300.0f, 500.0f}), pickle::math::Vector({400.0f, 400.0f}), pickle::math::Vector({500.0f, 550.0f}), {0x00, 0xFF, 0x00, 0xFF});
    renderer.drawTriangle(sdlRenderer, pickle::math::Vector({450.0f, 50.0f}), pickle::math::Vector({400.0f, 300.0f}), pickle::math::Vector({550.0f, 100.0f}), {0x00, 0x00, 0xFF, 0xFF});

    SDL_RenderPresent(sdlRenderer);

    while (!quit)
    {
        if (SDL_PollEvent(event) != 0)
        {
            if (event->type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
    return 0;
}