#include <pickle/light/direct_light.h>

pickle::renderer::DirectLight::DirectLight(math::Vector<3, float> ambient, math::Vector<3, float> diffuse, math::Vector<3, float> specular, math::Vector<3, float> direction) : Light(ambient, diffuse, specular), direction(direction)
{
}

pickle::math::Vector<3, float> pickle::renderer::DirectLight::getDirection() const
{
    return direction;
}