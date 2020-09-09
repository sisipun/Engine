#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/actor/actor.h"
#include "../engine/physics/body.h"

#include <string>

class Enemy : public Actor
{
public:
    Enemy(
        std::string name,
        Body body,
        float horizontalVelocity,
        float verticalVelocity,
        std::vector<std::string> tags = {"enemy"},
        std::vector<std::string> eventTypes = {},
        bool collider = true,
        bool visiable = true) : Actor(name,
                                      body,
                                      tags,
                                      eventTypes,
                                      horizontalVelocity,
                                      verticalVelocity,
                                      collider,
                                      visiable)
    {
    }

protected:
    void renderActor(SDL_Renderer *renderer) const override;

    void handleActorCollision(Actor *actor) override;
};

#endif