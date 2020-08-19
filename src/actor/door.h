#ifndef DOOR_H
#define DOOR_H

#include "../engine/actor/actor.h"
#include "../engine/physics/body.h"

#include <string>

class Door : public Actor
{
public:
    Door(std::string name, Body body) : Actor(
                                            name,
                                            body,
                                            { "door" },
                                            0,
                                            0,
                                            false,
                                            false) {}
};

#endif