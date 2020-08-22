#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "../actor/actor.h"
#include "event.h"

#include <map>
#include <string>
#include <vector>

class EventManager
{
public:
    bool subscribe(std::string eventType, Actor *actor);

    bool notifyEvent(Event event);

private:
    std::map<std::string, std::vector<Actor *>> subscribers;
};

#endif