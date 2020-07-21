#include "drunkard_walk_maze_generator.h"
#include <random>
#include <ctime>

int *DrunkardWalkMazeGenerator::generate(int width, int height)
{
    int step_count = width * height * (coverage / 100.0);
    int *maze = new int[width * height];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            *(maze + (i * height) + j) = 1;
        }
    }

    srand(time(0));

    int current_position_x = (rand() % (width / 3)) + (width / 3);
    int current_position_y = (rand() % (height / 3)) + (height / 3);

    for (int i = 0; i < step_count;)
    {
        int direction = rand() % 4;
        if (direction == 0 && current_position_x + 1 < width)
        {
            current_position_x += 1;
        }
        else if (direction == 1 && current_position_x - 1 >= 0)
        {
            current_position_x -= 1;
        }
        else if (direction == 2 && current_position_y + 1 < height)
        {
            current_position_y += 1;
        }
        else if (direction == 3 && current_position_y - 1 >= 0)
        {
            current_position_y -= 1;
        }

        if (*(maze + (current_position_x * height) + current_position_y) == 1)
        {
            *(maze + (current_position_x * height) + current_position_y) = 0;
            i++;
        }
    }

    return maze;
}