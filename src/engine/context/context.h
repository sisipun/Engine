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

    Actor *getActor(std::string name);

    std::map<std::string, Actor *> getActors();

    bool storeActor(Actor *actor);

    bool deleteActor(std::string name);

    bool subscribeEvent(std::string eventType, Actor *actor);

    bool notifyEvent(Event event);

private:
    Storage *storage;
    EventManager *eventManager;
};

#endif