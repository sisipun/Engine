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
        std::vector<std::string> tags = {"miniMap"},
        std::vector<std::string> eventTypes = {"heroUp", "heroDown", "heroLeft", "heroRight"},
        float horizontalVelocity = 0,
        float verticalVelocity = 0,
        bool manageCollisions = false,
        bool visiable = true) : Actor(name,
                                      body,
                                      tags,
                                      eventTypes,
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
        delete[] map;
    }

    bool moveLeft();

    bool moveRight();

    bool moveUp();

    bool moveDown();

protected:
    void renderActor(SDL_Renderer *renderer) override;

    void handleActorEvent(Event event) override;

private:
    int *map;
    int width;
    int height;
    int currentX;
    int currentY;
};

#endif