#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include <glm/glm.hpp>

#include "../bindable.h"

struct Texture
{
    unsigned int id;
    std::string type;
    std::string filePath;
};

class Material : public Bindable
{
public:
    Material(
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        std::vector<Texture> textures,
        float shiness,
        float shinessStrength) : ambient(ambient),
                                 diffuse(diffuse),
                                 specular(specular),
                                 textures(textures),
                                 shiness(shiness),
                                 shinessStrength(shinessStrength)
    {
    }

    void bind(const Shader &shader) const override;

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    std::vector<Texture> textures;
    float shiness;
    float shinessStrength;
};

#endif