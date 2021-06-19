#include "camera.h"

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors()
{
    front = glm::normalize(glm::vec3(
        cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
        sin(glm::radians(pitch)),
        cos(glm::radians(pitch)) * sin(glm::radians(yaw))));
    up = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(roll), front)) * glm::vec3(0.0f, 0.1f, 0.0f);
}