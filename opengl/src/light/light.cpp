#include "light.h"

#include <iostream>

void Light::bind(Shader const &shader) const
{
    shader.setVec3("light.ambient", ambient);
    shader.setVec3("light.diffuse", diffuse);
    shader.setVec3("light.specular", specular);
}