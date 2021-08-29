#include "dir_light.h"

void DirLight::bind(Shader const &shader) const
{
    Light::bind(shader);
    shader.setVec3("light.direction", direction);
}