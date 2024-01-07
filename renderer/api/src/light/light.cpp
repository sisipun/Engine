#include <pickle/light/light.h>

pickle::renderer::Light::Light(math::Vector<3, float> ambient, math::Vector<3, float> diffuse, math::Vector<3, float> specular) : ambient(ambient), diffuse(diffuse), specular(specular)
{
}

pickle::math::Vector<3, float> pickle::renderer::Light::getAmbient() const
{
    return ambient;
}

pickle::math::Vector<3, float> pickle::renderer::Light::getDiffuse() const
{
    return diffuse;
}

pickle::math::Vector<3, float> pickle::renderer::Light::getSpecular() const
{
    return specular;
}