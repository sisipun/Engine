#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

void Camera::draw(Shader const &shader) const
{
    shader.setVec3("camera.position", position);
    shader.setMat4("view", glm::lookAt(position, position + front, up));
    shader.setMat4("projection", glm::perspective(glm::radians(fov), aspectRatio, 0.1f, range));
}

void Camera::updateCameraVectors()
{
    front = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
    up = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(roll), front)) * glm::vec3(0.0f, 0.1f, 0.0f);
}