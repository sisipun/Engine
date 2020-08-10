#include "cellular_automata_generator.h"

const int MIN_WIDTH = 10;
const int MIN_HEIHGT = 10;

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

Map *CellularAutomataGenerator::generate(int width, int height, int birthLimit, int deathLimit,
                                         int initialChance, int stepCount, RandomGenerator generator)
{
    if (width <= 0 || height <= 0 || birthLimit < 0 || deathLimit < 0 || initialChance < 0 ||
        initialChance > 100 || stepCount < 0)
    {
        return new Map(nullptr, 0, 0, 0, 0);
    }
    else if (width < MIN_WIDTH || height < MIN_HEIHGT || initialChance == 0 || stepCount == 0)
    {
        int *empty = new int[height * width];
        MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, empty, width, height, 0);
        return new Map(empty, width, height, width / 2, height / 2);
    }

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