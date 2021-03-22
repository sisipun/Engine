#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL.h>

class Raycasting
{
public:
    Raycasting(int resolution) : resolution(resolution) {}

    bool isCorrectPoint(float x, float y);

    void drawMap(SDL_Renderer *renderer, int *map, int mapWidth, int mapHeight, float playerX, float playerY, float playerWidth, float playerHeight);

    void drawFov(SDL_Renderer *renderer, float startFovX, float startFovY, float fovAngel, float fovSize, float fovStep, int *map, int mapWidth, int mapHeight);

private:
    int resolution;
};

#endif