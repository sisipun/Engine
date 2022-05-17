#include "scene.h"

void Scene::update(SDL_Event event)
{
}

void Scene::draw() const
{
    shader.use();

    for (Bindable* bindable:  bindables)
    {
        bindable->bind(shader);
    }

    for (Drawable* drawable: drawables)
    {
        drawable->draw();
    }
}