#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm/glm.hpp>

#include "shader.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string filePath;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void draw(const Shader &shader) const;

private:
    unsigned int VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
};

#endif