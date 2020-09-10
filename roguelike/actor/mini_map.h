#ifndef MINI_MAP_H
#define MINI_MAP_H

#include "../../engine/actor/actor.h"

#include <string>

class MiniMap : public Actor
{
public:
    MiniMap(
        Body body,
        const int *map,
        int width,
        int height,
        int currentX,
        int currentY,
        std::string name = "miniMap",
        std::vector<std::string> tags = {"miniMap"},
        std::vector<std::string> eventTypes = {"heroUp", "heroDown", "heroLeft", "heroRight"},
        float horizontalVelocity = 0,
        float verticalVelocity = 0,
        bool collider = false,
        bool visiable = true) : Actor(name,
                                      body,
                                      tags,
                                      eventTypes,
                                      horizontalVelocity,
                                      verticalVelocity,
                                      collider,
                                      visiable),
                                map(new int[width * height]),
                                width(width),
                                height(height),
                                currentX(currentX),
                                currentY(currentY)
    {
        std::copy(map, map + (width * height), this->map);
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
    void renderActor(SDL_Renderer *renderer) const override;

    void handleActorEvent(Event event) override;

private:
    int *const map;
    const int width;
    const int height;
    int currentX;
    int currentY;
};

#endif