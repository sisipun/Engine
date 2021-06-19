#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 up, float pitch, float yaw, float roll, float fov) : position(position), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(up), pitch(pitch), yaw(yaw), roll(roll), fov(fov)
    {
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() const;

    float getFov() const {
        return fov;
    }

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float pitch;
    float yaw;
    float roll;
    float fov;

    void updateCameraVectors();
};

#endif