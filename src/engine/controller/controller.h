#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "../actor/actor.h"
#include "../storage/storage.h"

class Controller
{
public:
    virtual void handleInput(SDL_Event *event) = 0;

    virtual ~Controller() {}

    bool init(Storage *storage);

    std::string getActorName()
    {
        return actorName;
    }

protected:
    Controller(std::string actorName) : actorName(actorName), initialized(false), storage(nullptr), actor(nullptr)
    {
    }

    std::string actorName;
    bool initialized;
    Storage *storage;
    Actor *actor;
};

#endif