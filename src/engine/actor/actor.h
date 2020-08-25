#ifndef ACTOR_H
#define ACTOR_H

#include "../physics/body.h"
#include "../physics/collision.h"
#include "../context/context.h"
#include "../event/event.h"

#include "SDL.h"
#include <string>
#include <vector>

class Actor
{
public:
    virtual ~Actor()
    {
    }

    void render(SDL_Renderer *renderer) const
    {
        if (!visiable || context == nullptr)
        {
            return;
        }
        renderActor(renderer);
    }

    void update(float delta)
    {
        if (context == nullptr)
        {
            return;
        }
        updateActor(delta);
    }

    void handleInput(SDL_Event *event)
    {
        if (context == nullptr)
        {
            return;
        }
        handleActorInput(event);
    }

    void handleCollision(Actor *actor)
    {
        if (context == nullptr)
        {
            return;
        }
        handleActorCollision(actor);
    }

    void handleEvent(Event event)
    {
        if (context == nullptr)
        {
            return;
        }
        handleActorEvent(event);
    }

    virtual bool isCollides(Actor *actor) const
    {
        return checkCollision(body, actor->getBody());
    }

    Body getBody() const
    {
        return body;
    }

    const std::string getName() const
    {
        return name;
    }

    bool hasCollider() const
    {
        return collider;
    }

    const std::vector<std::string> getTags() const
    {
        return tags;
    }

    bool injectContext(Context *context)
    {
        this->context = context;
        for (std::string eventType : eventTypes)
        {
            this->context->subscribeEvent(eventType, this);
        }
        return true;
    }

protected:
    Actor(
        std::string name,
        Body body,
        std::vector<std::string> tags = {},
        std::vector<std::string> eventTypes = {},
        float horizontalVelocity = 0,
        float verticalVelocity = 0,
        bool collider = true,
        bool visiable = true) : name(name),
                                body(body),
                                tags(tags),
                                eventTypes(eventTypes),
                                horizontalVelocity(horizontalVelocity),
                                verticalVelocity(verticalVelocity),
                                collider(collider),
                                visiable(visiable),
                                context(nullptr)
    {
    }

    virtual void renderActor(SDL_Renderer *renderer) const;

    virtual void updateActor(float delta);

    virtual void handleActorInput(SDL_Event *event) {}

    virtual void handleActorCollision(Actor *actor) {}

    virtual void handleActorEvent(Event event) {}

    const std::string name;
    Body body;
    const std::vector<std::string> tags;
    const std::vector<std::string> eventTypes;
    float horizontalVelocity;
    float verticalVelocity;
    bool collider;
    bool visiable;
    Context *context;
};

#endif