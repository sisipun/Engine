#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm.hpp>

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float linear, float quadratic) : Light(ambient, diffuse, specular),
                                                                                                                              position(position),
                                                                                                                              linear(linear),
                                                                                                                              quadratic(quadratic)
    {
    }

    void draw(Shader const &shader) const override;

    glm::vec3 getPosition() const
    {
        return position;
    }

    void setPosition(glm::vec3 position)
    {
        this->position = position;
    }

private:
    glm::vec3 position;

    float linear;
    float quadratic;
};

#endif