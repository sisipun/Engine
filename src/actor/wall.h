#ifndef WALL_H
#define WALL_H

#include "../engine/actor/actor.h"
#include "../engine/physics/body.h"

#include <string>

class Wall : public Actor
{
public:
    Wall(std::string name, Body body, float horizontalVelocity, float verticalVelocity) : Actor(
                                                                                              name,
                                                                                              body,
                                                                                              horizontalVelocity,
                                                                                              verticalVelocity,
                                                                                              false,
                                                                                              true) {}
};

#endif