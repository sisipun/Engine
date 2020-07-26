#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

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

    ~Map() {
        delete[] map;
    }

    int* getValue() {
        return map;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    int getStartX() {
        return startX;
    }

    int getStartY() {
        return startY;
    }

private:
    int *map;
    int width;
    int height;
    int startX;
    int startY;
};

class MapGenerator
{
public:
    virtual ~MapGenerator() {}

    virtual Map *generate(int width, int height) = 0;
};

#endif