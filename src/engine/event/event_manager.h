#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "../actor/actor.h"
#include "event.h"

#include <map>
#include <string>

class EventManager
{
public:
    bool subsribe(Actor *actor);

    void notifyEvent(Event event);

private:
    std::map<std::string, Actor *> managedActors;
};

#endif