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

    ~Map()
    {
        delete[] map;
    }

    const int *const getValue() const
    {
        return map;
    }

    const int getWidth() const
    {
        return width;
    }

    const int getHeight() const
    {
        return height;
    }

    const int getStartX() const
    {
        return startX;
    }

    const int getStartY() const
    {
        return startY;
    }

private:
    const int *const map;
    const int width;
    const int height;
    const int startX;
    const int startY;
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