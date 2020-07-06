#ifndef ACTOR_H
#define ACTOR_H

#include "SDL.h"
#include "../physics/body.h"
#include <string>

class Actor
{
public:
    Actor(std::string name, Body body, float horizontalVelocity, float verticalVelocity) : name(name),
                                                                                           body(body),
                                                                                           horizontalVelocity(horizontalVelocity),
                                                                                           verticalVelocity(verticalVelocity) {}

    void render(SDL_Renderer *renderer);

    void update(float delta);

    void setVerticalVelocity(float verticalVelocity)
    {
        this->verticalVelocity = verticalVelocity;
    }

    void setHorizontalVelocity(float horizontalVelocity)
    {
        this->horizontalVelocity = horizontalVelocity;
    }

    std::string getName() {
        return name;
    }

private:
    std::string name;
    Body body;
    float horizontalVelocity;
    float verticalVelocity;
};

#endif