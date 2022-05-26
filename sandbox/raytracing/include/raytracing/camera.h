#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include <pickle/math.h>

class Camera
{
public:
    Camera(pickle::math::Vector<3, float> position, pickle::math::Matrix<4, 4, float> rotation) : position(position), rotation(rotation)
    {
    }

    pickle::math::Vector<3, float> getPosition() const
    {
        return position;
    }

    pickle::math::Matrix<4, 4, float> getRotation() const
    {
        return rotation;
    }

private:
    pickle::math::Vector<3, float> position;
    pickle::math::Matrix<4, 4, float> rotation;
};

#endif