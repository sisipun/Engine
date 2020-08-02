#ifndef ACTOR_H
#define ACTOR_H

#include "../physics/body.h"
#include "../physics/collision.h"
#include "../physics/rigid_body.h"

#include "SDL.h"
#include <string>

class Actor
{
public:
    virtual ~Actor()
    {
        delete rigidBody;
    }

    virtual void render(SDL_Renderer *renderer);

    virtual void update(float delta);

    virtual void handleInput(SDL_Event *event) {}

    virtual void handleCollision(Actor *actor) {}

    virtual bool isCollides(Actor *actor)
    {
        if (rigidBody == nullptr || actor->getRigidBody() == nullptr)
        {
            return false;
        }
        return checkCollision(rigidBody->getBody(), actor->getRigidBody()->getBody());
    }

    Body getBody()
    {
        return body;
    }

    std::string getName()
    {
        return name;
    }

    bool isManageCollisions()
    {
        return manageCollisions;
    }

    RigidBody *getRigidBody()
    {
        return rigidBody;
    }

protected:
    Actor(std::string name, Body body, float horizontalVelocity, float verticalVelocity, bool manageCollisions, bool hasRigid) : name(name),
                                                                                                                                 body(body),
                                                                                                                                 horizontalVelocity(horizontalVelocity),
                                                                                                                                 verticalVelocity(verticalVelocity),
                                                                                                                                 manageCollisions(manageCollisions)
    {
        if (hasRigid)
        {
            rigidBody = new RigidBody(body);
        }
        else
        {
            rigidBody = nullptr;
        }
    }

    Actor(std::string name, Body body, float horizontalVelocity, float verticalVelocity) : name(name),
                                                                                           body(body),
                                                                                           horizontalVelocity(horizontalVelocity),
                                                                                           verticalVelocity(verticalVelocity),
                                                                                           manageCollisions(false),
                                                                                           rigidBody(nullptr) {}

    Body body;
    RigidBody *rigidBody;
    float horizontalVelocity;
    float verticalVelocity;

private:
    std::string name;
    bool manageCollisions;
};

#endif