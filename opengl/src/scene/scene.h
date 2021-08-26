#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../light/light.h"
#include "../camera/camera.h"
#include "../model/model.h"
#include "../model/shader.h"

class Scene
{
public:
    Scene(std::vector<Model> models, Camera camera, Light light, Shader shader) : models(models),
                                                                                  camera(camera),
                                                                                  light(light),
                                                                                  shader(shader)
    {
        this->shader.load();
    }

    virtual void draw() const;

    Camera camera;

protected:
    std::vector<Model> models;
    Light light;
    Shader shader;
};

#endif