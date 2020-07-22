#include "simple_maze_generator.h"
#include "../random/random_generator.h"


int *SimpleMazeGenerator::generate(int width, int height)
{
    RandomGenerator generator = RandomGenerator();
    int size = width * height;
    int *maze = new int[size];

    for (int i = 0; i < size; i++)
    {
        *(maze + i) = generator.generateFromRange(0, 1);
    }

    return maze;
}