#ifndef SCENE_GENERATOR_H
#define SCENE_GENERATOR_H

#include "scene.h"
#include "../model/file_model.h"
#include "../light/dir_light.h"
#include "../light/point_light.h"

class SceneGenerator
{
public:
    static Scene simpleBox(float screenWidth, float screenHeight)
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
            0, 1, 2,
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

        std::vector<Material> materials = {
            {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), {}, 4.0f, 1.0f}};

        Mesh mesh(vertices, indices, materials);
        Model model({mesh});
        return Scene({model}, SceneGenerator::defaultCamera(screenWidth, screenHeight), SceneGenerator::defautlPointLight(), SceneGenerator::defaultShader());
    }

    static Scene backpack(float screenWidth, float screenHeight)
    {
        FileModel model("../resources/backpack/backpack.obj");
        return Scene({model}, SceneGenerator::defaultCamera(screenWidth, screenHeight), SceneGenerator::defautlPointLight(), SceneGenerator::defaultShader());
    }

private:
    static Camera defaultCamera(float screenWidth, float screenHeight)
    {
        return Camera(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.1f, 0.0f),
            float(screenWidth) / float(screenHeight),
            100.0f,
            0.0f,
            -90.0f,
            0.0f,
            90.0f);
    }

    static Shader defaultShader()
    {
        return Shader(
            "../resources/shaders/shader.vert",
            "../resources/shaders/shader.geom",
            "../resources/shaders/shader.frag");
    }

    static DirLight defautlDirLight()
    {
        return DirLight(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(3.0f, 3.0f, 3.0f));
    }

    static PointLight defautlPointLight()
    {
        return PointLight(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(3.0f, 3.0f, 3.0f), 1.0f, 2.0f);
    }
};

#endif
