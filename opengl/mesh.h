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
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    // TODO Shader const & and method const??
    void draw(Shader const &shader) const;

private:
    unsigned int VAO, VBO, EBO;
};

#endif