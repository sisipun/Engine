#ifndef MINI_MAP_H
#define MINI_MAP_H

#include "../engine/actor/actor.h"

#include <string>

class MiniMap : public Actor
{
public:
    MiniMap(Body body, int *map, int width, int height, int currentX, int currentY) : Actor("miniMap",
                                                                                            body,
                                                                                            { "miniMap" },
                                                                                            0,
                                                                                            0,
                                                                                            false,
                                                                                            true),
                                                                                      width(width),
                                                                                      height(height),
                                                                                      currentX(currentX),
                                                                                      currentY(currentY)
    {
        this->map = new int[width * height];
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                *(this->map + (i * height) + j) = *(map + (i * height) + j);
            }
        }
    }

    virtual ~MiniMap()
    {
        delete[] this->map;
    }

    bool moveLeft();

    bool moveRight();

    bool moveUp();

    bool moveDown();

    void renderActor(SDL_Renderer *renderer) override;

private:
    int *map;
    int width;
    int height;
    int currentX;
    int currentY;
};

#endif