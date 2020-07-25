#ifndef MAP_H
#define MAP_H

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

#endif