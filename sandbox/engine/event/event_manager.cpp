#include "event_manager.h"

bool EventManager::subscribe(std::string eventType, Actor *actor)
{
    std::map<std::string, std::vector<Actor *>>::iterator it = subscribers.find(eventType);
    if (it == subscribers.end())
    {
        subscribers.insert(std::pair<std::string, std::vector<Actor *>>(eventType, std::vector<Actor *>{actor}));
    }
    else
    {
        subscribers[eventType].push_back(actor);
    }
    return true;
}

bool EventManager::pushEvent(Event event)
{
    events.push_back(event);
    return true;
}

bool EventManager::notifyEvents()
{
    bool notifiedAny = false;
    for (Event event : events)
    {
        std::string eventType = event.getType();
        std::map<std::string, std::vector<Actor *>>::iterator it = subscribers.find(eventType);
        if (it != subscribers.end())
        {
            for (auto subscriber : subscribers[eventType])
            {
                subscriber->handleEvent(event);
            }
            notifiedAny = true;
        }
    }

    events.clear();
    return notifiedAny;
}