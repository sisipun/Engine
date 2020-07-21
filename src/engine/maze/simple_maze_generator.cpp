#include "simple_maze_generator.h"
#include <random>
#include <ctime>

int *SimpleMazeGenerator::generate(int width, int height)
{
    int size = width * height;
    int *maze = new int[size];

    srand(time(0));

    for (int i = 0; i < size; i++)
    {
        *(maze + i) = rand() % 5;
    }

    return maze;
}