#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <vector>
#include <SDL.h>

struct Body
{
    float x, y, width, height;

    bool contains(float x, float y)
    {
        return x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height;
    }
};

class Raycasting
{
public:
    Raycasting(int resolution) : resolution(resolution) {}

    bool isCorrectPoint(float x, float y);

    void drawMap(SDL_Renderer *renderer, std::vector<Body> bodies, float playerX, float playerY, float playerWidth, float playerHeight);

    void drawFov(SDL_Renderer *renderer, std::vector<Body> bodies, float playerX, float playerY, float fovAngel, float fovSize, float fovStep);

private:
    int resolution;
};

#endif