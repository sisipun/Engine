#include "event_manager.h"
#include "../utils/logger/logger.h"

bool EventManager::subsribe(Actor *actor)
{
    if (managedActors.find(actor->getName()) != managedActors.end())
    {
        Logger::log("Duplicate actor name: %s\n", actor->getName().c_str());
        return false;
    }
    managedActors.insert(std::pair<std::string, Actor *>(actor->getName(), actor));
    return true;
}

void EventManager::notifyEvent(Event event)
{
    for (auto managedDef : managedActors)
    {
        managedDef.second->handleEvent(event);
    }
}