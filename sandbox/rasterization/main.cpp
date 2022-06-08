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
    renderer.drawLine(sdlRenderer, pickle::math::Vector<2, int>({100, 100}), pickle::math::Vector<2, int>({500, 500}), {0xFF, 0xFF, 0xFF, 0xFF});
    renderer.drawLine(sdlRenderer, pickle::math::Vector<2, int>({400, 300}), pickle::math::Vector<2, int>({200, 200}), {0xFF, 0xFF, 0xFF, 0xFF});
    renderer.drawLine(sdlRenderer, pickle::math::Vector<2, int>({100, 500}), pickle::math::Vector<2, int>({500, 500}), {0xFF, 0xFF, 0xFF, 0xFF});
    renderer.drawLine(sdlRenderer, pickle::math::Vector<2, int>({100, 100}), pickle::math::Vector<2, int>({100, 500}), {0xFF, 0x00, 0x00, 0xFF});
    renderer.drawTriangle(sdlRenderer, pickle::math::Vector<2, int>({200, 400}), pickle::math::Vector<2, int>({300, 200}), pickle::math::Vector<2, int>({400, 400}), {0x00, 0x00, 0xFF, 0xFF});

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