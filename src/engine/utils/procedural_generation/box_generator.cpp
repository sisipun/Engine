#include "box_generator.h"
#include <vector>

const int MIN_WIDTH = 10;
const int MIN_HEIHGT = 10;

Map *BoxGenerator::generate(int width, int height, int eraseCount, int roomCount, int roomInitSize, RandomGenerator generator)
{
    if (width <= 0 || height <= 0 || eraseCount <= 0 || roomCount <= 0 ||
        roomInitSize <= 0 || width < (roomCount * roomInitSize) || height < (roomCount * roomInitSize))
    {
        return new Map(nullptr, 0, 0, 0, 0);
    }
    else if (width < MIN_WIDTH || height < MIN_HEIHGT)
    {
        int *empty = new int[height * width];
        MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, empty, width, height, 0);
        return new Map(empty, width, height, width / 2, height / 2);
    }

    int size = width * height;
    int *map = new int[size];
    MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, map, width, height, 1);

    for (int i = 0; i < eraseCount;)
    {
        int eraseX = generator.generateFromRange(0, 2 * width / 3);
        int eraseY = generator.generateFromRange(0, 2 * height / 3);
        int eraseWidth = generator.generateFromRange(width / 3, width);
        int eraseHeight = generator.generateFromRange(height / 3, height);
        if (eraseX + eraseWidth > width || eraseY + eraseHeight > height)
        {
            continue;
        }
        MapGeneratorUtils::boxToMap(eraseX, eraseX + eraseWidth - 1, eraseY, eraseY + eraseHeight - 1, map, width, height, 0);
        i++;
    }

    std::vector<Room *> rooms;
    for (int i = 0; i < roomCount;)
    {
        int roomX = generator.generateFromRange(0, width - roomInitSize);
        int roomY = generator.generateFromRange(0, height - roomInitSize);
        if (!MapGeneratorUtils::isEmpty(roomX, roomX + roomInitSize - 1, roomY, roomY + roomInitSize - 1, map, width, height))
        {
            continue;
        }

        MapGeneratorUtils::boxToMap(roomX, roomX + roomInitSize - 1, roomY, roomY + roomInitSize - 1, map, width, height, 2);
        rooms.push_back(new Room(roomX, roomY, roomInitSize, roomInitSize));

        i++;
    }

    bool extend = true;
    while (extend)
    {
        extend = false;
        for (Room *room : rooms)
        {
            extend = extend || room->extend(map, width, height);
        }
    }

    MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, map, width, height, 0);
    for (Room *room : rooms)
    {
        room->addToMap(map, width, height);
        delete room;
    }

    return new Map(map, width, height, width / 2, height / 2);
}

bool Room::extend(int *map, int mapWidth, int mapHeight)
{
    if (MapGeneratorUtils::isEmpty(x - 1, x - 1, y, y + height - 1, map, mapWidth, mapHeight))
    {
        MapGeneratorUtils::boxToMap(x - 1, x + width - 1, y, y + height - 1, map, mapWidth, mapHeight, 2);
        this->x--;
        this->width++;
        return true;
    }
    else if (MapGeneratorUtils::isEmpty(x, x + width - 1, y - 1, y - 1, map, mapWidth, mapHeight))
    {
        MapGeneratorUtils::boxToMap(x, x + width - 1, y - 1, y + height - 1, map, mapWidth, mapHeight, 2);
        this->y--;
        this->height++;
        return true;
    }
    else if (MapGeneratorUtils::isEmpty(x, x + width - 1, y + height, y + height, map, mapWidth, mapHeight))
    {
        MapGeneratorUtils::boxToMap(x, x + width - 1, y, y + height, map, mapWidth, mapHeight, 2);
        this->height++;
        return true;
    }
    else if (MapGeneratorUtils::isEmpty(x + width, x + width, y, y + height - 1, map, mapWidth, mapHeight))
    {
        MapGeneratorUtils::boxToMap(x, x + width, y, y + height - 1, map, mapWidth, mapHeight, 2);
        this->width++;
        return true;
    }

    return false;
}

bool Room::addToMap(int *map, int mapWidth, int mapHeight)
{
    MapGeneratorUtils::squareToMap(x, x + width - 1, y, y + height - 1, map, mapWidth, mapHeight, 1);
}