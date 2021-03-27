#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <vector>
#include <SDL.h>

struct Window
{
    float x, y, resolution;

    bool isCorrectPoint(float x, float y)
    {
        return x > 0 && y > 0 && x < resolution && y < resolution;
    }
};

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
    void render(SDL_Renderer *renderer, Window window, std::vector<Body> bodies, float playerX, float playerY, float fovAngel, float fovSize, float fovStep);
};

#endif