#include <cmath>

#include "raycasting.h"

std::vector<Body>::iterator findContains(std::vector<Body>* bodies, float x, float y)
{
    for (std::vector<Body>::iterator ptr = bodies->begin(); ptr < bodies->end(); ptr++)
    {
        if ((*ptr).contains(x, y))
        {
            return ptr;
        }
    }

    return bodies->end();
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

bool Raycasting::isCorrectPoint(float x, float y)
{
    return int(x) > 0 && int(y) > 0 && int(x) < resolution && int(y) < resolution;
}

void Raycasting::drawMap(SDL_Renderer *renderer, std::vector<Body> bodies, float playerX, float playerY, float playerWidth, float playerHeight)
{
    for (Body body : bodies)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect rect = {
            int(body.x),
            int(body.y),
            int(body.width),
            int(body.height)};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_Rect rect = {
        int(playerX),
        int(playerY),
        int(playerWidth),
        int(playerHeight)};
    SDL_RenderFillRect(renderer, &rect);
}

void Raycasting::drawFov(SDL_Renderer *renderer, std::vector<Body> bodies, float playerX, float playerY, float fovAngel, float fovSize, float fovStep)
{
    for (int i = 0; i < resolution; i++)
    {
        float currentAngel = fovAngel - fovSize / 2 + i * fovSize / resolution;
        float currentX = playerX;
        float currentY = playerY;
        float distance = 0;
        std::vector<Body>::iterator currentValue = bodies.end();
        while (isCorrectPoint(currentX, currentY) && (currentValue = findContains(&bodies, currentX, currentY)) == bodies.end())
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
            SDL_Rect rect = {
                int(currentX),
                int(currentY),
                int(fovStep),
                int(fovStep)};
            SDL_RenderFillRect(renderer, &rect);
            currentX = playerX + distance * cos(currentAngel);
            currentY = playerY - distance * sin(currentAngel);
            distance += fovStep;
        }
        if (currentValue != bodies.end())
        {
            float columnSize = int(resolution / sqrt(distance * cos(currentAngel - fovAngel)));
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_Rect rect = {
                int(resolution + i),
                int(resolution / 2 - columnSize / 2),
                int(1),
                int(columnSize)};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}