#ifndef SIMPLE_MAZE_GENERATOR_H
#define SIMPLE_MAZE_GENERATOR_H

#include "maze_generator.h"

class SimpleMazeGenerator : public MazeGenerator
{
public:
    int *generate(int width, int height) override;
};

#endif