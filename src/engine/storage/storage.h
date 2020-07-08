#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <map>

class Actor;
class Controller;

class Storage
{
public:
    ~Storage();

    bool addController(Controller *controller);

    bool addActor(Actor *actor);

    Actor *getActor(std::string name);

    Controller *getController(std::string actorName);

    std::map<std::string, Actor *> getActors()
    {
        return actors;
    }

    std::map<std::string, Controller *> getControllers()
    {
        return controllers;
    }

private:
    std::map<std::string, Actor *> actors;
    std::map<std::string, Controller *> controllers;
};

#endif