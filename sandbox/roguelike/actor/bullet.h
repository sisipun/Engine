#ifndef BULLET_H
#define BULLET_H

#include "../../engine/actor/actor.h"
#include "../../engine/physics/body.h"

#include <string>

class Bullet : public Actor
{
public:
    Bullet(
        std::string name,
        Body body,
        float horizontalVelocity,
        float verticalVelocity,
        std::vector<std::string> tags = {"bullet"},
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
    void handleActorCollision(Actor *actor) override;
};

#endif