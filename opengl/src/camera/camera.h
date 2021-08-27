#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "../bindable.h"

class Camera : public Bindable
{
public:
    Camera(glm::vec3 position,
           glm::vec3 up,
           float aspectRatio,
           float range,
           float pitch,
           float yaw,
           float roll,
           float fov) : position(position),
                        front(glm::vec3(0.0f, 0.0f, -1.0f)),
                        up(up),
                        aspectRatio(aspectRatio),
                        range(range),
                        pitch(pitch),
                        yaw(yaw),
                        roll(roll),
                        fov(fov)
    {
        updateCameraVectors();
    }

    void bind(Shader const &shader) const override;

    glm::mat4 getViewMatrix() const;

    glm::vec3 getPosition() const
    {
        return position;
    }

    void setPosition(glm::vec3 position)
    {
        this->position = position;
        updateCameraVectors();
    }

    float getPitch()
    {
        return pitch;
    }

    void setPitch(float pitch)
    {
        this->pitch = pitch;
        updateCameraVectors();
    }

    float getYaw()
    {
        return yaw;
    }

    void setYaw(float yaw)
    {
        this->yaw = yaw;
        updateCameraVectors();
    }

    float getRoll()
    {
        return roll;
    }

    void setRoll(float roll)
    {
        this->roll = roll;
        updateCameraVectors();
    }

    float getFov() const
    {
        return fov;
    }

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float aspectRatio;
    float range;

    float pitch;
    float yaw;
    float roll;
    float fov;

    void updateCameraVectors();
};

#endif