#include <glad/glad.h>

#include "material.h"

void Material::draw(const Shader &shader) const {
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;
    unsigned int normalNumber = 1;
    unsigned int heightNumber = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        Texture texture = textures[i];
        std::string type = texture.type;
        int number;
        if (type == "texture_diffuse")
        {
            number = diffuseNumber++;
        }
        else if (type == "texture_specular")
        {
            number = specularNumber++;
        }
        else if (type == "texture_normal")
        {
            number = normalNumber++;
        }
        else if (type == "texture_height")
        {
            number = specularNumber++;
        }

        shader.setInt("material." + type + std::to_string(number), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    shader.setFloat("material.shiness", shiness);
    shader.setFloat("material.shinessStrength", shinessStrength);
}