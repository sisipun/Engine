#include "storage.h"
#include "../actor/actor.h"
#include "../logger/logger.h"

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
    return true;
}

Actor *Storage::getActor(std::string name)
{
    std::map<std::string, Actor *>::iterator actorPair = actors.find(name);
    if (actorPair == actors.end())
    {
        return nullptr;
    }
    return actorPair->second;
}
