#ifndef DIR_LIGHT_H
#define DIR_LIGHT_H

#include <glm/glm.hpp>

#include "light.h"

class DirLight : public Light
{
public:
    DirLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) : Light(ambient, diffuse, specular), direction(direction)
    {
    }

    void draw(Shader const &shader) const override;

    glm::vec3 getDirection() const {
        return direction;
    }

    void setDirection(glm::vec3 direction) {
        this->direction = direction;
    }

private:
    glm::vec3 direction;
};

#endif