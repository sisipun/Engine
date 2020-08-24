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

std::map<std::string, Actor *> Context::getColliders()
{
    return storage->getColliders();
}

bool Context::storeActor(Actor *actor)
{
    return actor->injectContext(this) && storage->addActor(actor);
}

bool Context::deleteActor(std::string name)
{
    return storage->deleteActor(name);
}

bool Context::subscribeEvent(std::string eventType, Actor *actor)
{
    return eventManager->subscribe(eventType, actor);
}

bool Context::pushEvent(Event event)
{
    return eventManager->pushEvent(event);
}

bool Context::notifyEvents() {
    return eventManager->notifyEvents();
}