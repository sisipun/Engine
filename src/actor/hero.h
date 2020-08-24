#ifndef HERO_H
#define HERO_H

#include "../engine/actor/actor.h"
#include "../engine/physics/body.h"

#include <string>

class Hero : public Actor
{
public:
    Hero(
        Body body,
        float horizontalVelocity,
        float verticalVelocity,
        std::string name = "hero",
        std::vector<std::string> tags = {"hero"},
        std::vector<std::string> eventTypes = {},
        bool collider = true,
        bool visiable = true) : Actor(name,
                                      body,
                                      tags,
                                      eventTypes,
                                      horizontalVelocity,
                                      verticalVelocity,
                                      collider,
                                      visiable),
                                startX(body.x),
                                startY(body.y)
    {
    }

protected:
    void renderActor(SDL_Renderer *renderer) override;

    void updateActor(float delta) override;

    void handleActorInput(SDL_Event *event) override;

    void handleActorCollision(Actor *actor) override;

private:
    float lastHorizontalMove;
    float lastVerticalMove;
    float startX;
    float startY;
};

#endif