#ifndef BASE_BOX_SCENE_H
#define BASE_BOX_SCENE_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../light/dir_light.h"
#include "../../light/point_light.h"
#include "../scene.h"

class BaseBoxScene : public Scene
{
public:
    BaseBoxScene() : Scene(BaseBoxScene::boxModel(), BaseBoxScene::defaultCamera(), BaseBoxScene::defautlPointLight(), BaseBoxScene::defaultShader())
    {
    }

    void update(SDL_Event event) override
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                models[0].transform = glm::translate(models[0].transform, glm::vec3(0.1f, 0.0f, 0.0f));
                break;
            case SDLK_LEFT:
                models[0].transform = glm::translate(models[0].transform, glm::vec3(-0.1f, 0.0f, 0.0f));
                break;
            case SDLK_UP:
                models[0].transform = glm::translate(models[0].transform, glm::vec3(0.0f, 0.1f, 0.0f));
                break;
            case SDLK_DOWN:
                models[0].transform = glm::translate(models[0].transform, glm::vec3(0.0f, -0.1f, 0.0f));
                break;
            case SDLK_w:
                models[0].transform = glm::translate(models[0].transform, glm::vec3(0.0f, 0.0f, -0.1f));
                break;
            case SDLK_s:
                models[0].transform = glm::translate(models[0].transform, glm::vec3(0.0f, 0.0f, 0.1f));
                break;
            case SDLK_q:
                models[0].transform = glm::rotate(models[0].transform, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case SDLK_e:
                models[0].transform = glm::rotate(models[0].transform, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case SDLK_d:
                models[0].transform = glm::rotate(models[0].transform, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            case SDLK_a:
                models[0].transform = glm::rotate(models[0].transform, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            case SDLK_z:
                models[0].transform = glm::rotate(models[0].transform, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                break;
            case SDLK_c:
                models[0].transform = glm::rotate(models[0].transform, glm::radians(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                break;
            }
        }
    }

private:
    static Model boxModel()
    {
        std::vector<Vertex> vertices = {
            {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)},
            {glm::vec3(0.5f, 0.5f, 0.5), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f)}};

        std::vector<unsigned int> indices = {
            0, 2, 1,
            2, 3, 1,
            4, 5, 7,
            4, 7, 6,
            8, 10, 9,
            10, 11, 9,
            12, 13, 15,
            12, 15, 14,
            16, 17, 18,
            18, 17, 19,
            20, 23, 21,
            20, 22, 23};

        Material material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), {}, 32.0f, 0.5f);
        return Model(Mesh(vertices, indices, material));
    }

    static Camera defaultCamera()
    {
        return Camera(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.1f, 0.0f),
            4.0f / 3.0f,
            100.0f,
            0.0f,
            -90.0f,
            0.0f,
            90.0f);
    }

    static Shader defaultShader()
    {
        return Shader(
            "../resources/shaders/default-shader.vert",
            "../resources/shaders/default-shader.frag");
    }

    static DirLight defautlDirLight()
    {
        return DirLight(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(3.0f, 3.0f, 3.0f));
    }

    static PointLight defautlPointLight()
    {
        return PointLight(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 2.0f);
    }
};

#endif