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

bool EventManager::notifyEvent(Event event)
{
    std::string eventType = event.getType();
    std::map<std::string, std::vector<Actor *>>::iterator it = subscribers.find(eventType);
    if (it == subscribers.end())
    {
        return false;
    }
    else
    {
        for (auto subscriber : subscribers[eventType])
        {
            subscriber->handleEvent(event);
        }
        return true;
    }
}