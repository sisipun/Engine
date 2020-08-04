#include "collision_manager.h"
#include "../utils/logger/logger.h"

void CollisionManager::manageCollision(std::map<std::string, Actor *> actors)
{
    for (auto managedDef : managedActors)
    {
        for (auto actorDef : actors)
        {
            if (managedDef.first != actorDef.first &&
                (managedDef.second->isCollides(actorDef.second) ||
                 actorDef.second->isCollides(managedDef.second)))
            {
                managedDef.second->handleCollision(actorDef.second);
            }
        }
    }
}

bool CollisionManager::addActor(Actor *actor)
{
    if (managedActors.find(actor->getName()) != managedActors.end())
    {
        Logger::log("Duplicate actor name: %s\n", actor->getName().c_str());
        return false;
    }
    if (actor->getRigidBody() == nullptr) {
        Logger::log("Actor with name: %s has no rigid body\n", actor->getName().c_str());
        return false;
    }
    managedActors.insert(std::pair<std::string, Actor *>(actor->getName(), actor));
    return true;
}

bool CollisionManager::deleteActor(std::string name)
{
    if (managedActors.find(name) == managedActors.end())
    {
        Logger::log("Hasn't actor with name: %s\n", name.c_str());
        return false;
    }
    managedActors.erase(name);
    return true;
}