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

    void render(SDL_Renderer *renderer);

    virtual void update(float delta);

    virtual void handleInput(SDL_Event *event) {}

    virtual void handleCollision(Actor *actor) {}

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
    Actor(std::string name,
          Body body,
          std::vector<std::string> tags = std::vector<std::string>(),
          float horizontalVelocity = 0,
          float verticalVelocity = 0,
          bool manageCollisions = true,
          bool visiable = true)
        : name(name),
          body(body),
          tags(tags),
          horizontalVelocity(horizontalVelocity),
          verticalVelocity(verticalVelocity),
          manageCollisions(manageCollisions),
          visiable(visiable)
    {
    }

    Body body;
    std::vector<std::string> tags;
    float horizontalVelocity;
    float verticalVelocity;

    virtual void renderActor(SDL_Renderer *renderer);

private:
    std::string name;
    bool manageCollisions;
    bool visiable;
};

#endif