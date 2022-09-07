#include <rasterization/camera.h>

Camera::Camera(pickle::math::Vector<3, float> position, pickle::math::Vector<3, float> target) : position(position), target(target)
{
}

pickle::math::Matrix<4, 4, float> Camera::getViewMatrix() const
{
    pickle::math::Vector<3, float> up({0.0f, 1.0f, 0.0f});
    pickle::math::Vector<3, float> cameraDirection = normalize(target - position);
    pickle::math::Vector<3, float> cameraRight = normalize(cross(up, cameraDirection));
    pickle::math::Vector<3, float> cameraUp = cross(cameraDirection, cameraRight);

    return pickle::math::Matrix<4, 4, float>({cameraRight.data[0], cameraRight.data[1], cameraRight.data[2], -dot(cameraRight, position),
                                              cameraUp.data[0], cameraUp.data[1], cameraUp.data[2], -dot(cameraUp, position),
                                              cameraDirection.data[0], cameraDirection.data[1], cameraDirection.data[2], -dot(cameraDirection, position),
                                              0.0f, 0.0f, 0.0f, 1.0f});
}

pickle::math::Vector<3, float> Camera::getViewDirection() const
{
    return normalize(target - position);
}