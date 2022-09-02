#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <pickle/math.h>

struct Model
{
    std::vector<pickle::math::Vector<6, float>> vertices;
    std::vector<pickle::math::Vector<3, int>> triangles;
};

#endif