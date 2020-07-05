#ifndef ACTOR_INFO_H
#define ACTOR_INFO_H

#include "SDL.h"
#include "../physics/body.h"
#include "string"

class ActorInfo
{
public:
    ActorInfo(std::string name, Body body, float horizontalVelocity, float verticalVelocity) : name(name),
                                                                                               body(body),
                                                                                               horizontalVelocity(horizontalVelocity),
                                                                                               verticalVelocity(verticalVelocity) {}

    std::string getName()
    {
        return name;
    }

    Body getBody() {
        return body;
    }

    float getHorizontalVelocity() {
        return horizontalVelocity;
    }

    float getVerticalVelocity() {
        return verticalVelocity;
    }

private:
    std::string name;
    Body body;
    float horizontalVelocity;
    float verticalVelocity;
};

#endif