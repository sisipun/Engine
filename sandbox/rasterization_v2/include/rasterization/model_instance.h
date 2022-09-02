#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include <pickle/math.h>
#include <rasterization/model.h>

struct ModelInstance
{
    Model model;
    pickle::math::Matrix<4, 4, float> transform;
};

#endif