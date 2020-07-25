#include "cellular_automata_generator..h"
#include "../random/random_generator.h"

int countAliveNeighbours(int *maze, int width, int height, int x, int y)
{
    int count = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int neighbourX = x + i;
            int neighbourY = y + j;
            if (i == 0 && j == 0)
            {
                break;
            }
            else if (neighbourX < 0 || neighbourY < 0 || neighbourX >= width || neighbourY >= height)
            {
                count = count + 1;
            }
            else if (*(maze + (neighbourX * height) + neighbourY) == 1)
            {
                count = count + 1;
            }
        }
    }

    return count;
}

int *doSimulationStep(int *maze, int width, int height, int birthLimit, int deathLimit)
{
    int size = width * height;
    int *newMap = new int[size];

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int nbs = countAliveNeighbours(maze, width, height, x, y);
            if (*(maze + (x * height) + y) == 1)
            {
                if (nbs < deathLimit)
                {
                    *(newMap + (x * height) + y) = 0;
                }
                else
                {
                    *(newMap + (x * height) + y) = 1;
                }
            }
            else
            {
                if (nbs > birthLimit)
                {
                    *(newMap + (x * height) + y) = 1;
                }
                else
                {
                    *(newMap + (x * height) + y) = 0;
                }
            }
        }
    }
    delete[] maze;
    return newMap;
}

Map *CellularAutomataMazeGenerator::generate(int width, int height)
{
    RandomGenerator generator = RandomGenerator();
    int size = width * height;
    int *map = new int[size];

    for (int i = 0; i < size; i++)
    {
        int chance = generator.generateFromRange(1, 100);
        if (initialChance > chance)
        {
            *(map + i) = 1;
        }
        else
        {
            *(map + i) = 0;
        }
    }

    for (int i = 0; i < stepCount; i++)
    {
        map = doSimulationStep(map, width, height, birthLimit, deathLimit);
    }

    return new Map(map, width, height, width / 2, height / 2);
}