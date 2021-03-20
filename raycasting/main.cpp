#include <cmath>
#include <SDL.h>

void drawMap(SDL_Renderer *renderer, int *map, int mapWidth, int mapHeight, int rectWidth, int rectHeight)
{
    for (int i = 0; i < mapWidth; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            if (map[i + j * mapWidth] != 0)
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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

void drawFov(SDL_Renderer *renderer, float startFovX, float startFovY, float fovAngel, float fovSize, float fovItemSize, float fovStep, int *map, int mapWidth, int mapHeight, int rectWidth, int rectHeight)
{
    for (float currentAngel = fovAngel - fovSize / 2; currentAngel < fovAngel + fovSize / 2; currentAngel += fovStep)
    {
        float currentX = startFovX;
        float currentY = startFovY;
        float distance = 0;
        while (int(currentX) > 0 && int(currentY) > 0 && int(currentX) < mapWidth * rectWidth && int(currentY) < mapHeight * rectHeight && map[int(currentX / rectWidth) + int(currentY / rectHeight) * mapWidth] == 0)
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
            SDL_Rect rect = {
                int(currentX),
                int(currentY),
                int(fovItemSize),
                int(fovItemSize)};
            SDL_RenderFillRect(renderer, &rect);
            currentX = startFovX + distance * cos(currentAngel);
            currentY = startFovY - distance * sin(currentAngel);
            distance += fovItemSize;
        }
    }
}

int main(int argc, char *argv[])
{
    int winWidth = 800;
    int winHeight = 600;
    int mapWidth = 16;
    int mapHeight = 12;
    int map[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    float playerX = 100;
    float playerY = 100;
    float playerWidth = 10;
    float playerHeight = 10;
    float playerAngel = 3 * M_PI / 2;
    float playerFov = M_PI / 3;
    float fovItemSize = 3;
    float fovStep = M_PI / 365;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
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

    int rectWidth = winWidth / mapWidth;
    int rectHeight = winHeight / mapHeight;
    drawMap(renderer, map, mapWidth, mapHeight, rectWidth, rectHeight);
    drawPlayer(renderer, playerX, playerY, playerWidth, playerHeight);
    drawFov(renderer, playerX + playerWidth / 2 - fovItemSize / 2, playerY + playerHeight / 2 - fovItemSize / 2, playerAngel, playerFov, fovItemSize, fovStep, map, mapWidth, mapHeight, rectWidth, rectHeight);

    SDL_RenderPresent(renderer);

    bool quit = false;
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
}