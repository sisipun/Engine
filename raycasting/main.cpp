#include <SDL.h>

#include "raycasting.h"

int main(int argc, char *argv[])
{
    float resolution = 400;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution * 2, resolution,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        return -1;
    }

    SDL_Event *event = new SDL_Event();

    int mapWidth = 16;
    int mapHeight = 16;
    int map[] = {
        1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 2, 2, 1, 3, 3, 3, 1, 3, 1, 1, 1, 1, 1, 1,
    };
    float playerX = 150;
    float playerY = 100;
    float playerHorizontalVelocity = 0;
    float playerVerticalVelocity = 0;
    float playerSpeed = 1;
    float playerWidth = 10;
    float playerHeight = 10;
    float playerAngel = 3 * M_PI / 2;
    float playerFov = M_PI / 3;
    float playerFovStep = 3;
    Raycasting *raycasting = new Raycasting(resolution);

    bool quit = false;
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        raycasting->drawMap(renderer, map, mapWidth, mapHeight, playerX, playerY, playerWidth, playerHeight);
        raycasting->drawFov(renderer, playerX + playerWidth / 2, playerY + playerHeight / 2, playerAngel, playerFov, playerFovStep, map, mapWidth, mapHeight);
        SDL_RenderPresent(renderer);
        if (raycasting->isCorrectPoint(playerX + playerHorizontalVelocity, playerY) && map[int((playerX + playerHorizontalVelocity) * mapWidth / resolution) + int(playerY * mapHeight / resolution) * mapWidth] == 0)
        {
            playerX += playerHorizontalVelocity;
        }
        if (raycasting->isCorrectPoint(playerX, playerY + playerVerticalVelocity) && map[int(playerX * mapWidth / resolution) + int((playerY + playerVerticalVelocity) * mapHeight / resolution) * mapWidth] == 0)
        {
            playerY += playerVerticalVelocity;
        }
        playerAngel += M_PI / 365;
        if (SDL_PollEvent(event) != 0)
        {
            if (event->type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event->type == SDL_KEYDOWN)
            {
                switch (event->key.keysym.sym)
                {
                case SDLK_w:
                    playerVerticalVelocity = -playerSpeed;
                    break;
                case SDLK_s:
                    playerVerticalVelocity = playerSpeed;
                    break;
                case SDLK_a:
                    playerHorizontalVelocity = -playerSpeed;
                    break;
                case SDLK_d:
                    playerHorizontalVelocity = playerSpeed;
                    break;
                }
            }
            else if (event->type == SDL_KEYUP)
            {
                switch (event->key.keysym.sym)
                {
                case SDLK_w:
                    playerVerticalVelocity = 0;
                    break;
                case SDLK_s:
                    playerVerticalVelocity = 0;
                    break;
                case SDLK_a:
                    playerHorizontalVelocity = 0;
                    break;
                case SDLK_d:
                    playerHorizontalVelocity = 0;
                    break;
                }
            }
        }
    }
}