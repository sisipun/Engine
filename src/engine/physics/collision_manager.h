#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "../actor/actor.h"

#include <map>
#include <string>

class CollisionManager
{
public:
    bool addActor(Actor *actor);

    bool deleteActor(std::string name);

    void manageCollision(std::map<std::string, Actor *> actors);

private:
    std::map<std::string, Actor *> managedActors;
};

#endif