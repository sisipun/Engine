#ifndef DRUNKARD_WALK_GENERATOR_H
#define DRUNKARD_WALK_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class DrunkardWalkGenerator
{
public:
    Map *generate(int width, int height, int coverage = 50, RandomGenerator generator = RandomGenerator()) const;
};

#endif