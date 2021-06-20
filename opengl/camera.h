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

    glm::vec3 getPosition() const {
        return position;
    }

    void setPosition(glm::vec3 position) {
        this->position = position;
        updateCameraVectors();
    }

    void setPitch(float pitch) {
        this->pitch = pitch;
        updateCameraVectors();
    }

    void setYaw(float yaw) {
        this->yaw = yaw;
        updateCameraVectors();
    }

    void setRoll(float roll) {
        this->roll = roll;
        updateCameraVectors();
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