#ifndef MINI_MAP_H
#define MINI_MAP_H

#include "../engine/actor/actor.h"

#include <string>

class MiniMap : public Actor
{
public:
    MiniMap(
        Body body,
        int *map,
        int width,
        int height,
        int currentX,
        int currentY,
        std::string name = "miniMap",
        std::vector<std::string> tags ={ "miniMap" },
        float horizontalVelocity = 0,
        float verticalVelocity = 0,
        bool manageCollisions = false,
        bool visiable = true
    ) : Actor(
        name,
        body,
        tags,
        horizontalVelocity,
        verticalVelocity,
        manageCollisions,
        visiable),
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