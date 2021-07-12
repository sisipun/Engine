#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "shader.h"

class Light
{
public:
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : ambient(ambient), diffuse(diffuse), specular(specular)
    {
    }

    virtual void draw(Shader const &shader) const;

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif