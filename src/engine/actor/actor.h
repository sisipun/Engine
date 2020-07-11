#ifndef ACTOR_H
#define ACTOR_H

#include "../physics/body.h"

#include "SDL.h"
#include <string>

class Actor
{
public:
    virtual ~Actor() {}

    virtual void render(SDL_Renderer *renderer);

    virtual void update(float delta);

    virtual void handleInput(SDL_Event *event) {}

    Body getBody()
    {
        return body;
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

private:
    std::string name;
    Body body;
    float horizontalVelocity;
    float verticalVelocity;
};

#endif