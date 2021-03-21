#include <cmath>
#include <vector>
#include <SDL.h>

bool isCorrectPoint(float x, float y, int resolution)
{
    return int(x) > 0 && int(y) > 0 && int(x) < resolution && int(y) < resolution;
}

void setColor(SDL_Renderer *renderer, int value)
{
    if (value == 0)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    }
    if (value == 1)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    }
    else if (value == 2)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
    }
    else if (value == 3)
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    }
}

void drawMap(SDL_Renderer *renderer, int *map, int mapWidth, int mapHeight, int resolution)
{
    int rectWidth = resolution / mapWidth;
    int rectHeight = resolution / mapHeight;
    for (int i = 0; i < mapWidth; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            if (map[i + j * mapWidth] != 0)
            {
                setColor(renderer, map[i + j * mapWidth]);
                SDL_Rect rect = {
                    i * rectWidth,
                    j * rectHeight,
                    rectWidth,
                    rectHeight};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void drawPlayer(SDL_Renderer *renderer, float playerX, float playerY, float playerWidth, float playerHeight)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_Rect rect = {
        int(playerX),
        int(playerY),
        int(playerWidth),
        int(playerHeight)};
    SDL_RenderFillRect(renderer, &rect);
}

void drawFov(SDL_Renderer *renderer, float startFovX, float startFovY, float fovAngel, float fovSize, float fovStep, int *map, int mapWidth, int mapHeight, int resolution)
{
    for (int i = 0; i < resolution; i++)
    {
        float currentAngel = fovAngel - fovSize / 2 + i * fovSize / resolution;
        float currentX = startFovX;
        float currentY = startFovY;
        float distance = 0;
        int currentValue = 0;
        while (
            isCorrectPoint(currentX, currentY, resolution) &&
            (currentValue = map[int(currentX * mapWidth / resolution) + int(currentY * mapHeight / resolution) * mapWidth]) == 0)
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
            SDL_Rect rect = {
                int(currentX),
                int(currentY),
                int(fovStep),
                int(fovStep)};
            SDL_RenderFillRect(renderer, &rect);
            currentX = startFovX + distance * cos(currentAngel);
            currentY = startFovY - distance * sin(currentAngel);
            distance += fovStep;
        }
        float columnSize = int(resolution / sqrt(distance * cos(currentAngel - fovAngel)));
        setColor(renderer, currentValue);
        SDL_Rect rect = {
            int(resolution + i),
            int(resolution / 2 - columnSize / 2),
            int(1),
            int(columnSize)};
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char *argv[])
{
    float resolution = 400;
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

    SDL_RenderPresent(renderer);

    bool quit = false;
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        drawMap(renderer, map, mapWidth, mapHeight, resolution);
        drawPlayer(renderer, playerX, playerY, playerWidth, playerHeight);
        drawFov(renderer, playerX + playerWidth / 2, playerY + playerHeight / 2, playerAngel, playerFov, playerFovStep, map, mapWidth, mapHeight, resolution);
        SDL_RenderPresent(renderer);
        if (isCorrectPoint(playerX + playerHorizontalVelocity, playerY, resolution) && map[int((playerX + playerHorizontalVelocity) * mapWidth / resolution) + int(playerY * mapHeight / resolution) * mapWidth] == 0)
        {
            playerX += playerHorizontalVelocity;
        }
        if (isCorrectPoint(playerX, playerY + playerVerticalVelocity, resolution) && map[int(playerX * mapWidth / resolution) + int((playerY + playerVerticalVelocity) * mapHeight / resolution) * mapWidth] == 0)
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