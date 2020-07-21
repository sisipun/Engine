#include "chess_maze_generator.h"
#include <random>
#include <ctime>

int *ChessMazeGenerator::generate(int width, int height)
{
    int size = width * height;
    int *maze = new int[size];

    for (int i = 0; i < width; i++) {
        *(maze + (i * height)) = 1;
        *(maze + (i * height) + height - 1) = 1;
    }
    for (int j = 0; j < height; j++) {
        *(maze + j) = 1;
        *(maze + ((width - 1) * height) +j) = 1;
    }
    
    srand(time(0));

    for (int i = 2; i < width - 2; i += 2)
    {
        for (int j = 2; j < height - 2; j += 2)
        {
            *(maze + (i * height) + j) = 1;
            int addition = rand() % 4 + 1;
            if (addition == 1)
            {
                *(maze + ((i + 1) * height) + j) = 1;
            }
            else if (addition == 2)
            {
                *(maze + ((i - 1) * height) + j) = 1;
            }
            else if (addition == 3)
            {
                *(maze + (i * height) + (j + 1)) = 1;
            }
            else if (addition == 4)
            {
                *(maze + (i * height) + (j - 1)) = 1;
            }
        }
    }

    return maze;
}