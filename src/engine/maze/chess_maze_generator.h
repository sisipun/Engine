#ifndef CHESS_MAZE_GENERATOR_H
#define CHESS_MAZE_GENERATOR_H

#include "maze_generator.h"

class ChessMazeGenerator : public MazeGenerator
{
public:
    int *generate(int width, int height) override;
};

#endif