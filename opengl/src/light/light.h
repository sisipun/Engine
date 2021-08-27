#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "../bindable.h"

class Light : public Bindable
{
public:
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : ambient(ambient),
                                                                      diffuse(diffuse),
                                                                      specular(specular)
    {
    }

    virtual void bind(const Shader &shader) const override;

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif