#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "map.h"

class MapGenerator
{
public:
    virtual ~MapGenerator() {}

    virtual Map *generate(int width, int height) = 0;
};

#endif