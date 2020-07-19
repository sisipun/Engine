#include "drunkard_walk_maze_generator.h"
#include <stdlib.h>
#include "../logger/logger.h"
#include <random>

int *DrunkardWalkMazeGenerator::generate(int width, int height)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> directionUni(0, 3);
    std::uniform_int_distribution<int> positionXUni(static_cast<int>(width / 3), static_cast<int>(2 * width / 3));
    std::uniform_int_distribution<int> positionYUni(static_cast<int>(height / 3), static_cast<int>(2 * height / 3));

    int step_count = (width * height) / 2;
    int *maze = new int[width * height];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            *(maze + (i * height) + j) = 1;
        }
    }

    int current_position_x = positionXUni(rng);
    int current_position_y = positionYUni(rng);
    Logger::log("%d", current_position_x);
    Logger::log("%d", current_position_y);

    for (int i = 0; i < step_count;)
    {
        int direction = directionUni(rng);
        if (direction == 0)
        {
            current_position_x += 1;
            if (current_position_x >= width)
            {
                current_position_x -= 1;
                continue;
            }
        }
        else if (direction == 1)
        {
            current_position_x -= 1;
            if (current_position_x < 0)
            {
                current_position_x += 1;
                continue;
            }
        }
        else if (direction == 2)
        {
            current_position_y += 1;
            if (current_position_y >= height)
            {
                current_position_y -= 1;
                continue;
            }
        }
        else if (direction == 3)
        {
            current_position_y -= 1;
            if (current_position_y < 0)
            {
                current_position_y += 1;
                continue;
            }
        }

        if (*(maze + (current_position_x * height) + current_position_y) == 1)
        {
            *(maze + (current_position_x * height) + current_position_y) = 0;
            i++;
        }
    }

    return maze;
}