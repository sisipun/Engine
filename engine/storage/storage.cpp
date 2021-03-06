#include "storage.h"
#include "../utils/logger/logger.h"

Storage::~Storage()
{
    for (const auto &actorDef : actors)
    {
        delete actorDef.second;
    }

    actors.clear();
}

bool Storage::addActor(Actor *actor)
{
    if (actors.find(actor->getName()) != actors.end())
    {
        Logger::log("Duplicate actor name: %s\n", actor->getName().c_str());
        return false;
    }
    actors.insert(std::pair<std::string, Actor *>(actor->getName(), actor));
    if (actor->hasCollider()) {
        colliders.insert(std::pair<std::string, Actor *>(actor->getName(), actor));
    }
    return true;
}

bool Storage::deleteActor(std::string name) {
    if (actors.find(name) == actors.end())
    {
        Logger::log("Actor with name: %s not exitst\n", name.c_str());
        return false;
    }

    delete actors[name];
    actors.erase(name);

    if (colliders.find(name) != colliders.end()) {
        colliders.erase(name);
    }
    return true;
}

Actor *Storage::getActor(std::string name) const
{
    auto actorPair = actors.find(name);
    if (actorPair == actors.end())
    {
        Logger::log("Can't find actor with name: %s\n", name.c_str());
        return nullptr;
    }
    return actorPair->second;
}
