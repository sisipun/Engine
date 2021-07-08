#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include <glm/glm.hpp>

#include "shader.h"

struct Texture
{
    unsigned int id;
    std::string type;
    std::string filePath;
};

class Material
{
public:
    Material(std::vector<Texture> textures, float shiness, float shinessStrength) : textures(textures), shiness(shiness), shinessStrength(shinessStrength)
    {
    }

    void draw(const Shader &shader) const;

private:
    std::vector<Texture> textures;
    float shiness;
    float shinessStrength;
};

#endif