#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/glm.hpp>

#include "../bindable.h"
#include "material.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoords;
};

class Mesh : public Bindable
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);

    void bind(const Shader &shader) const override;

    void draw() const;

private:
    unsigned int VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;
};

#endif