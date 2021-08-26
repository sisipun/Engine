#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <glm/glm.hpp>

#include "shader.h"
#include "mesh.h"

class Model
{
public:
    Model() : Model(std::vector<Mesh>())
    {
    }

    Model(std::vector<Mesh> meshes) : meshes(meshes), transform(glm::mat4(1.0f))
    {
    }

    void draw(const Shader &shader) const;

protected:
    std::vector<Mesh> meshes;
    glm::mat4 transform;
};

#endif