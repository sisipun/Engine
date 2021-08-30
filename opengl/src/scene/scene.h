#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <SDL.h>

#include "../model/model.h"
#include "../model/shader.h"
#include "../bindable.h"

class Scene
{
public:
    Scene(Shader shader) : shader(shader)
    {
        this->shader.load();
    }

    virtual void draw() const;

    virtual void update(SDL_Event event);

protected:
    std::vector<Drawable*> drawables;
    std::vector<Bindable*> bindables;
    Shader shader;
};

#endif