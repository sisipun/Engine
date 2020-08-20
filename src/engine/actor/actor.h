#ifndef ACTOR_H
#define ACTOR_H

#include "../physics/body.h"
#include "../physics/collision.h"
#include "../physics/rigid_body.h"

#include "SDL.h"
#include <string>
#include <vector>

class Actor
{
public:
    virtual ~Actor()
    {
    }

    void render(SDL_Renderer *renderer) {
        if (!visiable)
        {
            return;
        }
        renderActor(renderer);
    }

    void update(float delta) {
        updateActor(delta);
    }

    void handleInput(SDL_Event *event) {
        handleActorInput(event);
    }

    void handleCollision(Actor *actor) {
        handleActorCollision(actor);
    }

    virtual bool isCollides(Actor *actor)
    {
        return checkCollision(body, actor->getBody());
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

    std::vector<std::string> getTags() {
        return tags;
    }

protected:
    Actor(
        std::string name,
        Body body,
        std::vector<std::string> tags = std::vector<std::string>(),
        float horizontalVelocity = 0,
        float verticalVelocity = 0,
        bool manageCollisions = true,
        bool visiable = true
    ) : name(name),
        body(body),
        tags(tags),
        horizontalVelocity(horizontalVelocity),
        verticalVelocity(verticalVelocity),
        manageCollisions(manageCollisions),
        visiable(visiable)
    {
    }

    virtual void renderActor(SDL_Renderer *renderer);

    virtual void updateActor(float delta);

    virtual void handleActorInput(SDL_Event *event) {}

    virtual void handleActorCollision(Actor *actor) {}

    std::string name;
    Body body;
    std::vector<std::string> tags;
    float horizontalVelocity;
    float verticalVelocity;
    bool manageCollisions;
    bool visiable;
};

#endif