#include "point_light.h"

#include <iostream>

void PointLight::bind(Shader const &shader) const
{
    Light::bind(shader);

    shader.setVec3("light.position", position);
    shader.setFloat("light.constant", 1.0f);
    shader.setFloat("light.linear", linear);
    shader.setFloat("light.quadratic", quadratic);
}