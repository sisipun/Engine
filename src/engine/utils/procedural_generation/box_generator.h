#ifndef BOX_GENERATOR_H
#define BOX_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class BoxGenerator
{
public:
    Map *generate(int width, int height, RandomGenerator generator = RandomGenerator());
};

#endif