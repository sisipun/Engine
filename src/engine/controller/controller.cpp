#include "controller.h"
#include "../engine.h"

bool Controller::init(Engine *engine)
{
    this->engine = engine;
    Actor *actor = this->engine->getActor(actorName);
    if (actor == nullptr)
    {
        return false;
    }

    this->actor = actor;
    initialized = true;

    return true;
}