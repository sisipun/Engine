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

    Actor *getActor(std::string name) const;

    std::map<std::string, Actor *> getActors() const
    {
        return actors;
    }

    std::map<std::string, Actor *> getColliders() const
    {
        return colliders;
    }

private:
    std::map<std::string, Actor *> actors;
    std::map<std::string, Actor *> colliders;
};

#endif