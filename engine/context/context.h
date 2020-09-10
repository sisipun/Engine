#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <map>

class Actor;
class Storage;
class EventManager;
class Event;

class Context
{
public:
    Context();

    ~Context();

    Actor *getActor(std::string name) const;

    std::map<std::string, Actor *> getActors() const;

    std::map<std::string, Actor *> getColliders() const;

    bool storeActor(Actor *actor);

    bool deleteActor(std::string name);

    bool subscribeEvent(std::string eventType, Actor *actor);

    bool pushEvent(Event event);

    bool notifyEvents();

private:
    Storage *storage;
    EventManager *eventManager;
};

#endif