#ifndef DRUNKARD_WALK_GENERATOR_H
#define DRUNKARD_WALK_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class DrunkardWalkGenerator
{
public:
    Map *generate(int width, int height, RandomGenerator generator = RandomGenerator(), int coverage = 50);
};

#endif