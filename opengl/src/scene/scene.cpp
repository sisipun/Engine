#include "scene.h"

void Scene::update(SDL_Event event)
{
}

void Scene::draw() const
{
    shader.use();

    for (int i = 0; i < bindables.size(); i++)
    {
        bindables[i]->bind(shader);
    }

    for (int i = 0; i < models.size(); i++)
    {
        models[i]->draw();
    }
}