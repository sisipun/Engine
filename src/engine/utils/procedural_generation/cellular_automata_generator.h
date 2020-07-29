#ifndef CELLULAR_AUTOMATA_GENERATOR_H
#define CELLULAR_AUTOMATA_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class CellularAutomataGenerator
{
public:
    Map *generate(int width, int height, RandomGenerator generator = RandomGenerator(),
                  int birthLimit = 4, int deathLimit = 3, int initialChance = 50, int stepCount = 4);
};

#endif