#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : vertices(vertices), indices(indices), textures(textures)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, textureCoords));

    glBindVertexArray(0);
}

void Mesh::draw(const Shader &shader) const
{
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;
    unsigned int normalNumber = 1;
    unsigned int heightNumber = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        Texture texture = textures[i];
        std::string type = texture.type;
        std::string number;
        if (type == "texture_diffuse")
        {
            number = std::to_string(diffuseNumber++);
        }
        else if (type == "texture_specular")
        {
            number = std::to_string(specularNumber++);
        }
        else if (type == "texture_normal")
        {
            number = std::to_string(normalNumber++);
        }
        else if (type == "texture_height")
        {
            number = std::to_string(specularNumber++);
        }

        shader.setInt("material." + type + number, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}