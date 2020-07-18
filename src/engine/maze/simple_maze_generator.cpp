#include "simple_maze_generator.h"
#include <stdlib.h>

int *SimpleMazeGenerator::generate(int width, int height)
{
    int size = width * height;
    int *maze = new int[size];
    for (int i = 0; i < size; i++)
    {
        *(maze + i) = rand() % 5;
    }

    return maze;
}