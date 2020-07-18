#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

class MazeGenerator
{
public:
    virtual ~MazeGenerator() {}

    virtual int *generate(int width, int height) = 0;
};

#endif