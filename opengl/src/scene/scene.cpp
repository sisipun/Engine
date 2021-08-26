#include "scene.h"

#include <iostream>

void Scene::draw() const
{
    shader.use();
    camera.draw(shader);
    light.draw(shader);

    for (int i = 0; i < models.size(); i++)
    {
        models[i].draw(shader);
    }
}