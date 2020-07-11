#ifndef SCENE_H
#define SCENE_H

#include "../storage/storage.h"

#include "SDL.h"

class Scene
{
public:
    virtual ~Scene() {}

    bool init(Storage *storage)
    {
        this->storage = storage;
        this->initialized = true;
        return initialized;
    }

    void renderScene(SDL_Renderer *renderer)
    {
        if (!initialized)
        {
            return;
        }
        render(renderer);
    }

    void updateScene(float delta)
    {
        if (!initialized)
        {
            return;
        }
        update(delta);
    }

    void handleInputScene(SDL_Event *event)
    {
        if (!initialized)
        {
            return;
        }
        handleInput(event);
    }

protected:
    Scene() : storage(nullptr), initialized(false) {}

    virtual void render(SDL_Renderer *renderer) = 0;

    virtual void update(float delta) = 0;

    virtual void handleInput(SDL_Event *event) = 0;

    Storage *storage;

private:
    bool initialized;
};

#endif