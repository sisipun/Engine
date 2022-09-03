#ifndef CAMERA_H
#define CAMERA_H

#include <pickle/math.h>

class Camera
{
public:
    Camera(pickle::math::Vector<3, float> position, pickle::math::Vector<3, float> target);

    pickle::math::Matrix<4, 4, float> getViewMatrix() const;

private:
    pickle::math::Vector<3, float> position;
    pickle::math::Vector<3, float> target;
};

#endif