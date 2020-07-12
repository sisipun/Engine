#ifndef SCENE_H
#define SCENE_H

#include "../storage/storage.h"

#include "SDL.h"

class Scene
{
public:
    virtual ~Scene() {}

    virtual bool init(Storage *storage) = 0;

    virtual void render(SDL_Renderer *renderer) = 0;

    virtual void update(float delta) = 0;

    virtual void handleInput(SDL_Event *event) = 0;
};

#endif