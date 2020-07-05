#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "../actor/actor.h"

class Engine;

class Controller
{
public:
    virtual void handleInput(SDL_Event *event) = 0;

    bool init(Engine *engine);

    std::string getActorName()
    {
        return actorName;
    }

protected:
    Controller(std::string actorName) : actorName(actorName), initialized(false), engine(nullptr), actor(nullptr)
    {
    }

    std::string actorName;
    bool initialized;
    Engine *engine;
    Actor *actor;
};

#endif