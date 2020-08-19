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
                                                                            { "hero" },
                                                                            horizontalVelocity,
                                                                            verticalVelocity,
                                                                            true,
                                                                            true) {}

    void update(float delta) override;

    void handleInput(SDL_Event *event) override;

    void handleCollision(Actor *actor) override;

    void renderActor(SDL_Renderer *renderer) override;

private:
    float lastHorizontalMove;
    float lastVerticalMove;
};

#endif