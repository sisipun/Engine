#ifndef ACTOR_H
#define ACTOR_H

#include "SDL.h"
#include "../physics/body.h"
#include "actor_info.h"

class Actor
{
public:
    Actor(ActorInfo *info);

    void render(SDL_Renderer *renderer);

    void update(float delta);

    void setVerticalVelocity(float verticalVelocity);

    void setHorizontalVelocity(float horizontalVelocity); 

    Body getBody();

private:
    Body body;
    float horizontalVelocity;
    float verticalVelocity;
};

#endif