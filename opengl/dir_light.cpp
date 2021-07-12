#include "dir_light.h"

void DirLight::draw(Shader const &shader) const {
    Light::draw(shader);
    shader.setVec3("light.direction", direction);
}