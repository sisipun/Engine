#include <iostream>
#include "SDL.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event *event;
bool quit = false;

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 300, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Log("Hello\n");
    event = new SDL_Event();

    while(!quit) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {0, 0, 100, 100};
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(event) != 0) {
            if (event->type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}