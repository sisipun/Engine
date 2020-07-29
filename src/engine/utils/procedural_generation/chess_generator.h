#ifndef CHESS_GENERATOR_H
#define CHESS_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class ChessGenerator
{
public:
    Map *generate(int width, int height, RandomGenerator generator = RandomGenerator());
};

#endif