#include <pickle/light/point_light.h>

pickle::renderer::PointLight::PointLight(math::Vector<3, float> ambient, math::Vector<3, float> diffuse, math::Vector<3, float> specular, math::Vector<3, float> position, math::Vector<3, float> direction) : Light(ambient, diffuse, specular), position(position), direction(direction)
{
}

pickle::math::Vector<3, float> pickle::renderer::PointLight::getPosition() const
{
    return position;
}

pickle::math::Vector<3, float> pickle::renderer::PointLight::getDirection() const
{
    return direction;
}