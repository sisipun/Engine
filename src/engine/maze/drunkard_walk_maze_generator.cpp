#include "drunkard_walk_maze_generator.h"
#include "../random/random_generator.h"

int *DrunkardWalkMazeGenerator::generate(int width, int height)
{
    RandomGenerator generator = RandomGenerator();
    int step_count = width * height * (coverage / 100.0);
    int *maze = new int[width * height];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            *(maze + (i * height) + j) = 1;
        }
    }

    int current_position_x = generator.generateFromRange(width / 3, 2 * width / 3);
    int current_position_y = generator.generateFromRange(height / 3, 2 * height / 3);

    for (int i = 0; i < step_count;)
    {
        int direction = generator.generateFromRange(0, 3);
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