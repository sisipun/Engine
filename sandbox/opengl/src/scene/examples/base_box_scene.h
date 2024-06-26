#ifndef BASE_BOX_SCENE_H
#define BASE_BOX_SCENE_H

#include <vector>

#include "../scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../util/camera_util.h"
#include "../../util/light_util.h"
#include "../../util/model_util.h"
#include "../../util/shader_util.h"

class BaseBoxScene : public Scene
{
public:
    BaseBoxScene() : Scene(ShaderUtil::pointLightShader()),
                     camera(CameraUtil::defaultCamera()),
                     light(LightUtil::pointLight()),
                     model(ModelUtil::box())
    {
        bindables.push_back(&this->camera);
        bindables.push_back(&this->light);
        bindables.push_back(&this->model);

        drawables.push_back(&this->model);
    }

    void update(SDL_Event event) override
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                model.transform = glm::translate(model.transform, glm::vec3(0.1f, 0.0f, 0.0f));
                break;
            case SDLK_LEFT:
                model.transform = glm::translate(model.transform, glm::vec3(-0.1f, 0.0f, 0.0f));
                break;
            case SDLK_UP:
                model.transform = glm::translate(model.transform, glm::vec3(0.0f, 0.1f, 0.0f));
                break;
            case SDLK_DOWN:
                model.transform = glm::translate(model.transform, glm::vec3(0.0f, -0.1f, 0.0f));
                break;
            case SDLK_w:
                model.transform = glm::translate(model.transform, glm::vec3(0.0f, 0.0f, -0.1f));
                break;
            case SDLK_s:
                model.transform = glm::translate(model.transform, glm::vec3(0.0f, 0.0f, 0.1f));
                break;
            case SDLK_q:
                model.transform = glm::rotate(model.transform, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case SDLK_e:
                model.transform = glm::rotate(model.transform, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case SDLK_d:
                model.transform = glm::rotate(model.transform, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            case SDLK_a:
                model.transform = glm::rotate(model.transform, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            case SDLK_z:
                model.transform = glm::rotate(model.transform, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                break;
            case SDLK_c:
                model.transform = glm::rotate(model.transform, glm::radians(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                break;
            }
        }
    }

private:
    Model model;
    Camera camera;
    PointLight light;
};

#endif