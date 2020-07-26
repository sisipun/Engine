#ifndef CHESS_MAZE_GENERATOR_H
#define CHESS_MAZE_GENERATOR_H

#include "map_generator.h"

class ChessGenerator : public MapGenerator
{
public:
    Map *generate(int width, int height) override;
};

#endif