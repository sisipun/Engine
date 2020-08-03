#include "box_generator.h"

const int ERASE_COUNT = 4;
const int ROOM_COUNT = 3;

Map *BoxGenerator::generate(int width, int height, RandomGenerator generator)
{
    int size = width * height;
    int *map = new int[size];
    MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, map, width, height, 1);

    for (int i = 0; i < ERASE_COUNT;)
    {
        int eraseX = generator.generateFromRange(0, 2 * width / 3);
        int eraseY = generator.generateFromRange(0, 2 * height / 3);
        int eraseWidth = generator.generateFromRange(width / 3, width);
        int eraseHeight = generator.generateFromRange(height / 3, height);
        if (eraseX + eraseWidth > width || eraseY + eraseHeight > height) {
            continue;
        }
        MapGeneratorUtils::boxToMap(eraseX, eraseX + eraseWidth - 1, eraseY, eraseY + eraseHeight - 1, map, width, height, 0);
        i++;
    }

    return new Map(map, width, height, width / 2, height / 2);
}