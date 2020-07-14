#ifndef ACTOR_GROUP_H
#define ACTOR_GROUP_H

#include "actor.h"

#include "SDL.h"
#include <string>
#include <vector>

class ActorGroup : public Actor
{
public:
    ActorGroup(std::string name, std::vector<Actor *> children)
        : Actor(name, {0, 0, 0, 0}, 0, 0, false), children(children) {}

    void render(SDL_Renderer *renderer) override
    {
        for (auto child : children)
        {
            child->render(renderer);
        }
    }

    void update(float delta) override
    {
        for (auto child : children)
        {
            child->update(delta);
        }
    }

    void handleInput(SDL_Event *event) override
    {
        for (auto child : children)
        {
            child->handleInput(event);
        }
    }

    virtual bool isCollides(Actor *actor) override
    {
        for (auto child : children)
        {
            if (child->isCollides(actor))
            {
                return true;
            };
        }
        return false;
    }

private:
    std::vector<Actor *> children;
};

#endif