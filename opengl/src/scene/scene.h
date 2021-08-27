#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <SDL.h>

#include "../light/point_light.h"
#include "../camera/camera.h"
#include "../model/model.h"
#include "../model/shader.h"

class Scene
{
public:
    Scene(Model model, Camera camera, PointLight light, Shader shader) : Scene(std::vector<Model>{model},
                                                                          camera,
                                                                          light,
                                                                          shader)
    {
    }

    Scene(std::vector<Model> models, Camera camera, PointLight light, Shader shader) : models(models),
                                                                                       camera(camera),
                                                                                       light(light),
                                                                                       shader(shader)
    {
        this->shader.load();
    }

    virtual void draw() const;

    virtual void update(SDL_Event event);

    Camera camera;

protected:
    std::vector<Model> models;
    PointLight light;
    Shader shader;
};

#endif