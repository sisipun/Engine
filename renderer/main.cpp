#include <SDL.h>

#include <fstream>
#include <iostream>
#include <sstream>

#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f

void drawLine(SDL_Renderer *renderer, float x1, float y1, float x2, float y2)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (float i = 0.0f; i < 1.0f; i += 0.01)
    {
        float x = i * x1 + (1 - i) * x2;
        float y = i * y1 + (1 - i) * y2;
        SDL_Rect rect = {
            static_cast<int>(x * SCREEN_WIDTH),
            static_cast<int>(y * SCREEN_HEIGHT),
            static_cast<int>(1.0f),
            static_cast<int>(1.0f)};
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Can't load SDL module" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Can't create window" << std::endl;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created" << std::endl;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        drawLine(renderer, 0.2, 0.2, 0.8, 0.8);

        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}