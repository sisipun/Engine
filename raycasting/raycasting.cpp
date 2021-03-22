#include <cmath>

#include "raycasting.h"

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

bool Raycasting::isCorrectPoint(float x, float y)
{
    return int(x) > 0 && int(y) > 0 && int(x) < resolution && int(y) < resolution;
}

void Raycasting::drawMap(SDL_Renderer *renderer, int *map, int mapWidth, int mapHeight, float playerX, float playerY, float playerWidth, float playerHeight)
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
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_Rect rect = {
        int(playerX),
        int(playerY),
        int(playerWidth),
        int(playerHeight)};
    SDL_RenderFillRect(renderer, &rect);
}

void Raycasting::drawFov(SDL_Renderer *renderer, float startFovX, float startFovY, float fovAngel, float fovSize, float fovStep, int *map, int mapWidth, int mapHeight)
{
    for (int i = 0; i < resolution; i++)
    {
        float currentAngel = fovAngel - fovSize / 2 + i * fovSize / resolution;
        float currentX = startFovX;
        float currentY = startFovY;
        float distance = 0;
        int currentValue = 0;
        while (
            isCorrectPoint(currentX, currentY) &&
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