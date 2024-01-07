#include <pickle/camera.h>

pickle::renderer::Camera::Camera(pickle::math::Vector<3, float> cameraPosition, pickle::math::Vector<3, float> lookAtPosition) : cameraPosition(cameraPosition), lookAtPosition(lookAtPosition)
{
}

pickle::math::Matrix<4, 4, float> pickle::renderer::Camera::getView() const
{
    return pickle::math::lookAt<pickle::math::CoordinateSystemType::RIGHT_HANDED>(
        cameraPosition,
        lookAtPosition,
        pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}));
}

pickle::math::Vector<3, float> pickle::renderer::Camera::getPosition() const
{
    return cameraPosition;
}