#ifndef HERO_H
#define HERO_H

#include "../engine/actor/actor.h"
#include "../engine/physics/body.h"

#include <string>

class Hero : public Actor
{
public:
    Hero(Body body, float horizontalVelocity, float verticalVelocity) : Actor(
                                                                            "hero",
                                                                            body,
                                                                            horizontalVelocity,
                                                                            verticalVelocity) {}

    void handleInput(SDL_Event *event) override;
};

#endif