#ifndef HERO_H
#define HERO_H

#include "../utils/constants.h"

#include "../engine/actor/actor.h"
#include "../engine/physics/body.h"

#include <string>
#include <vector>

class Hero : public Actor
{
public:
    Hero(
        Body body,
        float horizontalVelocity = 0,
        float verticalVelocity = 0,
        std::string name = "hero",
        std::vector<std::string> tags = {"hero"},
        std::vector<std::string> eventTypes = {"deleteBullet"},
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
    void renderActor(SDL_Renderer *renderer) const override;

    void updateActor(float delta) override;

    void handleActorInput(SDL_Event *event) override;

    void handleActorCollision(Actor *actor) override;

    void handleActorEvent(Event event) override;

private:
    float lastHorizontalMove;
    float lastVerticalMove;
    float startX;
    float startY;
    std::vector<std::string> bullets;
};

#endif