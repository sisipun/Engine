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

void Raycasting::drawMap(SDL_Renderer *renderer, Window window, std::vector<Body> bodies, float playerX, float playerY, float playerWidth, float playerHeight)
{
    for (Body body : bodies)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect rect = {
            int(window.x + body.x),
            int(window.y + body.y),
            int(body.width),
            int(body.height)};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_Rect rect = {
        int(window.x + playerX),
        int(window.y + playerY),
        int(playerWidth),
        int(playerHeight)};
    SDL_RenderFillRect(renderer, &rect);
}

void Raycasting::drawFov(SDL_Renderer *renderer, Window window, std::vector<Body> bodies, float playerX, float playerY, float fovAngel, float fovSize, float fovStep)
{
    for (int i = 0; i < window.resolution; i++)
    {
        float currentAngel = fovAngel - fovSize / 2 + i * fovSize / window.resolution;
        float currentX = playerX;
        float currentY = playerY;
        float distance = 0;
        std::vector<Body>::iterator currentValue = bodies.end();
        while (window.isCorrectPoint(currentX, currentY) && (currentValue = findContains(&bodies, currentX, currentY)) == bodies.end())
        {
            currentX = playerX + distance * cos(currentAngel);
            currentY = playerY - distance * sin(currentAngel);
            distance += fovStep;
        }
        if (currentValue != bodies.end())
        {
            float columnSize = int(window.resolution / sqrt(distance * cos(currentAngel - fovAngel)));
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_Rect rect = {
                int(window.x + i),
                int(window.y + window.resolution / 2 - columnSize / 2),
                int(1),
                int(columnSize)};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}