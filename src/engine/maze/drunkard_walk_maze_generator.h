#ifndef DRUNKARD_WALK_MAZE_GENERATOR_H
#define DRUNKARD_WALK_MAZE_GENERATOR_H

#include "maze_generator.h"

class DrunkardWalkMazeGenerator : public MazeGenerator
{
public:
    int *generate(int width, int height) override;
};

#endif