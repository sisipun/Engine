#ifndef BOX_GENERATOR_H
#define BOX_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class BoxGenerator
{
public:
    Map *generate(int width, int height, RandomGenerator generator = RandomGenerator());
};

class Room
{
public:
    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    bool extend(int *map, int mapWidth, int mapHeight);

    bool addToMap(int *map, int mapWidth, int mapHeight);

private:
    int x, y, width, height;
};

#endif