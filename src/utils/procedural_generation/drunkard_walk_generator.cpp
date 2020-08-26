#include "drunkard_walk_generator.h"
#include "../../engine/utils/logger/logger.h"

const int MIN_WIDTH = 3;
const int MIN_HEIHGT = 3;

Map *DrunkardWalkGenerator::generate(int width, int height, int coverage, RandomGenerator generator) const
{
    if (width < 0 || height < 0 || coverage < 0 || coverage > 100)
    {
        Logger::log(
            "Invalid params: \nwidth = %d (Should be more than zero) \
            \nheight = %d (Should be more than zero) \
            \ncoverage = %d (Should be in range from 0 to 100)",
            width,
            height,
            coverage);
        return new Map(nullptr, 0, 0, 0, 0);
    }
    else if (width == 0 || height == 0 || coverage == 0)
    {
        int *empty = new int[height * width];
        MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, empty, width, height, 0);
        return new Map(empty, width, height, width / 2, height / 2);
    }

    int size = width * height;
    int step_count = size * (coverage / 100.0);
    int *map = new int[size];
    MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, map, width, height, 1);

    int starterPositionX = generator.generateFromRange(width / 3, 2 * width / 3);
    int starterPositionY = generator.generateFromRange(height / 3, 2 * height / 3);

    int currentPositionX = starterPositionX;
    int currentPositionY = starterPositionY;

    *(map + (currentPositionX * height) + currentPositionY) = 0;

    bool moveX = true;
    for (int i = 1; i < step_count;)
    {
        int changeDirection = generator.generateFromRange(0, 10);
        if (changeDirection == 0)
        {
            moveX = !moveX;
        }
        int direction = generator.generateFromRange(0, 1);

        if (moveX)
        {
            if (direction == 0 && currentPositionX + 1 < width)
            {
                currentPositionX += 1;
            }
            else if (direction == 1 && currentPositionX - 1 >= 0)
            {
                currentPositionX -= 1;
            }
        }
        else
        {
            if (direction == 0 && currentPositionY + 1 < height)
            {
                currentPositionY += 1;
            }
            else if (direction == 1 && currentPositionY - 1 >= 0)
            {
                currentPositionY -= 1;
            }
        }

        if (*(map + (currentPositionX * height) + currentPositionY) == 1)
        {
            *(map + (currentPositionX * height) + currentPositionY) = 0;
            i++;
        }
    }

    return new Map(map, width, height, starterPositionX, starterPositionY);
}