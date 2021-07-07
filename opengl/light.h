#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "shader.h"

class Light
{
public:
    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : position(position), ambient(ambient), diffuse(diffuse), specular(specular)
    {
    }

    void draw(Shader const &shader) const;

    glm::vec3 getPosition() const {
        return position;
    }

    void setPosition(glm::vec3 position) {
        this->position = position;
    }

private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif