#include "controller.h"

bool Controller::init(Storage *storage)
{
    this->storage = storage;
    Actor *actor = this->storage->getActor(actorName);
    if (actor == nullptr)
    {
        return false;
    }

    this->actor = actor;
    initialized = true;

    return true;
}