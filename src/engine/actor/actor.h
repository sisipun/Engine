#ifndef ACTOR_H
#define ACTOR_H

#include "SDL.h"
#include "../physics/body.h"
#include <string>

class Actor
{
public:
    virtual ~Actor() {}

    void render(SDL_Renderer *renderer);

    void update(float delta);

    virtual void handleInput(SDL_Event *event) {}

    void setVerticalVelocity(float verticalVelocity)
    {
        this->verticalVelocity = verticalVelocity;
    }

    void setHorizontalVelocity(float horizontalVelocity)
    {
        this->horizontalVelocity = horizontalVelocity;
    }

    void setBody(Body body)
    {
        this->body = body;
    }

    std::string getName()
    {
        return name;
    }

protected:
    Actor(std::string name, Body body, float horizontalVelocity, float verticalVelocity) : name(name),
                                                                                           body(body),
                                                                                           horizontalVelocity(horizontalVelocity),
                                                                                           verticalVelocity(verticalVelocity) {}

private:
    std::string name;
    Body body;
    float horizontalVelocity;
    float verticalVelocity;
};

#endif