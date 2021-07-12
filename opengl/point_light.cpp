#include "point_light.h"

void PointLight::draw(Shader const &shader) const {
    Light::draw(shader);
    shader.setVec3("light.position", position);
    shader.setFloat("light.constant", 1.0f);
    shader.setFloat("light.linear", linear);
    shader.setFloat("light.quadratic", quadratic);
}