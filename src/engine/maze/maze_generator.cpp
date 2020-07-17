#include "maze_generator.h"
#include <stdlib.h>

int *MazeGenerator::generate(int width, int height)
{
    int size = width * height;
    int *maze = new int[size];
    for (int i = 0; i < size; i++)
    {
        *(maze + i) = rand() % 5;
    }

    return maze;
}