#ifndef STORAGE_H
#define STORAGE_H

#include "../actor/actor.h"

#include <string>
#include <map>

class Storage
{
public:
    ~Storage();

    bool addActor(Actor *actor);

    bool deleteActor(std::string name);

    Actor *getActor(std::string name);

    std::map<std::string, Actor *> getActors()
    {
        return actors;
    }

private:
    std::map<std::string, Actor *> actors;
};

#endif