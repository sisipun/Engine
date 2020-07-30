#ifndef SCENE_H
#define SCENE_H

#include "../../storage/storage.h"
#include "../actor.h"

#include "SDL.h"
#include <string>
#include <vector>

class Scene
{
public:
    Scene(std::vector<std::string> actorNames) : actorNames(actorNames) {}

    bool init(Storage *storage)
    {
        for (auto actorName : actorNames)
        {
            Actor *actor = storage->getActor(actorName);
            if (actor == nullptr)
            {
                actors.clear();
                return false;
            }
            actors.push_back(actor);
        }
        return true;
    }

    void render(SDL_Renderer *renderer)
    {
        for (auto actor : actors)
        {
            actor->render(renderer);
        }
    }

    void update(float delta)
    {
        for (auto actor : actors)
        {
            actor->update(delta);
        }
    }

    void handleInput(SDL_Event *event)
    {
        for (auto actor : actors)
        {
            actor->handleInput(event);
        }
    }

private:
    std::vector<std::string> actorNames;
    std::vector<Actor *> actors;
};

#endif