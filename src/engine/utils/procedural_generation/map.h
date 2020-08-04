#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "../logger/logger.h"

class Map
{
public:
    Map(int *map, int width, int height, int startX, int startY) : map(map),
                                                                   width(width),
                                                                   height(height),
                                                                   startX(startX),
                                                                   startY(startY)
    {
    }

    ~Map()
    {
        delete[] map;
    }

    int *getValue()
    {
        return map;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    int getStartX()
    {
        return startX;
    }

    int getStartY()
    {
        return startY;
    }

private:
    int *map;
    int width;
    int height;
    int startX;
    int startY;
};

class MapGeneratorUtils
{
public:
    static void squareToMap(int startX, int endX, int startY, int endY, int *map, int mapWidht, int mapHeight, int value)
    {
        for (int i = startX; i <= endX; i++)
        {
            *(map + (i * mapHeight) + startY) = value;
            *(map + (i * mapHeight) + endY) = value;
        }
        for (int j = startY; j <= endY; j++)
        {
            *(map + (startX * mapHeight) + j) = value;
            *(map + (endX * mapHeight) + j) = value;
        }
    }

    static void boxToMap(int startX, int endX, int startY, int endY, int *map, int mapWidht, int mapHeight, int value)
    {
        for (int i = startX; i <= endX; i++)
        {
            for (int j = startY; j <= endY; j++)
            {
                *(map + (i * mapHeight) + j) = value;
            }
        }
    }

    static bool isEmpty(int startX, int endX, int startY, int endY, int *map, int mapWidth, int mapHeight)
    {
        if (startX < 0 || startY < 0 || endX >= mapWidth || endY >= mapHeight)
        {
            return false;
        }

        for (int i = startX; i <= endX; i++)
        {
            for (int j = startY; j <= endY; j++)
            {
                if (*(map + (i * mapHeight) + j) != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }
};

#endif