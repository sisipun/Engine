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
                                                                            verticalVelocity,
                                                                            true,
                                                                            true) {}

    void update(float delta) override;

    void handleInput(SDL_Event *event) override;

    void handleCollision(Actor *actor) override;

private:
    float lastHorizontalMove;
    float lastVerticalMove;
};

#endif