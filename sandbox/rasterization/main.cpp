#include <SDL.h>
#include <pickle/math.h>

void drawPoint(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect rect = {x, y, 1, 1};
    SDL_RenderFillRect(renderer, &rect);
}

void drawLine(SDL_Renderer *renderer, pickle::math::Vector<2, int> start, pickle::math::Vector<2, int> end)
{
    bool swapped = false;
    if (std::abs(end.data[1] - start.data[1]) > std::abs(end.data[0] - start.data[0]))
    {
        std::swap(start.data[0], start.data[1]);
        std::swap(end.data[0], end.data[1]);
        swapped = true;
    }
    if (start.data[0] > end.data[0])
    {
        std::swap(start, end);
    }
    float a = float(end.data[1] - start.data[1]) / float(end.data[0] - start.data[0]);
    float b = start.data[0] - a * start.data[1];
    for (int x = start.data[0]; x < end.data[0]; x++)
    {
        int y = a * x + b;
        if (swapped)
        {
            drawPoint(renderer, y, x);
        }
        else
        {
            drawPoint(renderer, x, y);
        }
    }
}

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

    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);

    // Render
    drawLine(sdlRenderer, pickle::math::Vector<2, int>({100, 100}), pickle::math::Vector<2, int>({500, 500}));
    drawLine(sdlRenderer, pickle::math::Vector<2, int>({400, 300}), pickle::math::Vector<2, int>({200, 200}));
    drawLine(sdlRenderer, pickle::math::Vector<2, int>({100, 500}), pickle::math::Vector<2, int>({500, 500}));
    drawLine(sdlRenderer, pickle::math::Vector<2, int>({100, 100}), pickle::math::Vector<2, int>({100, 500}));

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