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

    Model(Mesh mesh) : Model(std::vector<Mesh>{mesh})
    {
    }

    Model(std::vector<Mesh> meshes) : meshes(meshes), transform(glm::mat4(1.0f))
    {
    }

    void draw(const Shader &shader) const;

    glm::mat4 transform;
protected:
    std::vector<Mesh> meshes;
};

#endif