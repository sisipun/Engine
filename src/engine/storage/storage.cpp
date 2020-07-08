#include "storage.h"
#include "../actor/actor.h"
#include "../controller/controller.h"
#include "../logger/logger.h"

Storage::~Storage()
{
    for (const auto &actorDef : actors)
    {
        delete actorDef.second;
    }

    actors.clear();

    for (const auto &controllerDef : controllers)
    {
        delete controllerDef.second;
    }

    controllers.clear();
}

bool Storage::addController(Controller *controller)
{
    if (!controller->init(this))
    {
        Logger::log("Can't initialize controller for actor name: %s\n", controller->getActorName().c_str());
        return false;
    }

    controllers.insert(std::pair<std::string, Controller *>(controller->getActorName(), controller));
    return true;
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

Controller *Storage::getController(std::string actorName)
{
    std::map<std::string, Controller *>::iterator controllerPair = controllers.find(actorName);
    if (controllerPair == controllers.end())
    {
        return nullptr;
    }
    return controllerPair->second;
}
