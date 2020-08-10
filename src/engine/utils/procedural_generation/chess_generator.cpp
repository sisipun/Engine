#include "chess_generator.h"

const int MIN_WIDTH = 3;
const int MIN_HEIHGT = 3;

Map *ChessGenerator::generate(int width, int height, RandomGenerator generator)
{
    if (width <= 0 || height <= 0)
    {
        return new Map(nullptr, 0, 0, 0, 0);
    } else if (width < MIN_WIDTH || height < MIN_HEIHGT)
    {
        int *empty = new int[height * width];
        MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, empty, width, height, 0);
        return new Map(empty, width, height, width / 2, height / 2);
    }
    int size = width * height;
    int *map = new int[size];
    MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, map, width, height, 0);

    for (int i = 0; i < width; i++)
    {
        *(map + (i * height)) = 1;
        *(map + (i * height) + height - 1) = 1;
    }
    for (int j = 0; j < height; j++)
    {
        *(map + j) = 1;
        *(map + ((width - 1) * height) + j) = 1;
    }

    for (int i = 2; i < width - 2; i += 2)
    {
        for (int j = 2; j < height - 2; j += 2)
        {
            *(map + (i * height) + j) = 1;
            int addition = generator.generateFromRange(0, 3);
            if (addition == 0)
            {
                *(map + ((i + 1) * height) + j) = 1;
            }
            else if (addition == 1)
            {
                *(map + ((i - 1) * height) + j) = 1;
            }
            else if (addition == 2)
            {
                *(map + (i * height) + (j + 1)) = 1;
            }
            else if (addition == 3)
            {
                *(map + (i * height) + (j - 1)) = 1;
            }
        }
    }

    return new Map(map, width, height, width / 2, height / 2);
}