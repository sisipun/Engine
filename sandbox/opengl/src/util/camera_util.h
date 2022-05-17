#ifndef CAMERA_UTIL_H
#define CAMERA_UTIL_H

#include "../camera/camera.h"

class CameraUtil
{
public:
    static Camera defaultCamera()
    {
        return Camera(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.1f, 0.0f),
            4.0f / 3.0f,
            100.0f,
            0.0f,
            -90.0f,
            0.0f,
            90.0f);
    }
};

#endif