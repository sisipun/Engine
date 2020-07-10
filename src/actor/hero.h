#ifndef HERO_H
#define HERO_H

#include "../engine/actor/actor.h"
#include <string>

class Hero : public Actor
{
public:
    Hero(std::string name, Body body, float horizontalVelocity, float verticalVelocity) : Actor(
                                                                                              name,
                                                                                              body,
                                                                                              horizontalVelocity,
                                                                                              verticalVelocity) {}

    void handleInput(SDL_Event *event) override;
};

#endif