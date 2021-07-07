#include "light.h"

void Light::draw(Shader const &shader) const {
    shader.setVec3("light.position", position);
    shader.setVec3("light.ambient", ambient);
    shader.setVec3("light.diffuse", diffuse);
    shader.setVec3("light.specular", specular);
}