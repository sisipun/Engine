#include "context.h"

#include "../actor/actor.h"
#include "../storage/storage.h"
#include "../event/event_manager.h"
#include "../event/event.h"

Context::Context() : storage(new Storage()), eventManager(new EventManager()) {}

Context::~Context()
{
    delete storage;
    delete eventManager;
}

Actor *Context::getActor(std::string name)
{
    return storage->getActor(name);
}

std::map<std::string, Actor *> Context::getActors()
{
    return storage->getActors();
}

bool Context::storeActor(Actor *actor)
{
    return actor->injectContext(this) && storage->addActor(actor);
}

bool Context::subscribeEvent(std::string eventType, Actor *actor)
{
    return eventManager->subscribe(eventType, actor);
}

bool Context::notifyEvent(Event event)
{
    return eventManager->notifyEvent(event);
}