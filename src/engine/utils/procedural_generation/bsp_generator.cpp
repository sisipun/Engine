#include "bsp_generator.h"
#include "../random/random_generator.h"
#include "../logger/logger.h"

Leaf *split(int startX, int endX, int startY, int endY, int splitCount, RandomGenerator generator)
{
    //Logger::log("%d - X: (%d - %d), Y(%d - %d)\n",
    //           splitCount,
    //            startX,
    //            endX,
    //            startY,
    //            endY);

    if (splitCount <= 0)
    {
        return nullptr;
    }

    int width = endX - startX;
    int height = endY - startY;
    int splitDirection = generator.generateFromRange(0, 1);
    Leaf *lLeaf, *rLeaf;

    if (splitDirection == 0)
    {
        int splitX = generator.generateFromRange(width / 3, 2 * width / 3);
        lLeaf = split(startX, startX + splitX, startY, endY, splitCount - 1, generator);
        rLeaf = split(startX + splitX, endX, startY, endY, splitCount - 1, generator);
    }
    else
    {
        int splitY = generator.generateFromRange(height / 3, 2 * height / 3);
        lLeaf = split(startX, endX, startY, startY + splitY, splitCount - 1, generator);
        rLeaf = split(startX, endX, startY + splitY, endY, splitCount - 1, generator);
    }

    return new Leaf(
        lLeaf,
        rLeaf,
        startX,
        endX,
        startY,
        endY);
}

void showMap(int *map, int mapWidth, int mapHeight)
{
    for (int i = 0; i < mapWidth; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            Logger::log("%d ", *(map + (i * mapHeight) + j));
        }
        Logger::log("\n");
    }
}

void leafToMap(Leaf *leaf, int *map, int mapWidth, int mapHeight)
{
    if (leaf->getLLeaf() != nullptr && leaf->getRLeaf() != nullptr)
    {
        leafToMap(leaf->getLLeaf(), map, mapWidth, mapHeight);
        leafToMap(leaf->getRLeaf(), map, mapWidth, mapHeight);
    }
    else
    {
        Logger::log("X: (%d - %d), Y(%d - %d)\n",
                    leaf->getStartX(),
                    leaf->getEndX(),
                    leaf->getStartY(),
                    leaf->getEndY());
        for (int i = leaf->getStartX(); i < leaf->getEndX(); i++)
        {
            *(map + (i * mapHeight) + leaf->getStartY()) = 1;
            *(map + (i * mapHeight) + (leaf->getEndY() - 1)) = 1;
        }
        for (int j = leaf->getStartY(); j < leaf->getEndY(); j++)
        {
            *(map + (leaf->getStartX() * mapHeight) + j) = 1;
            *(map + ((leaf->getEndX() - 1) * mapHeight) + j) = 1;
        }
        showMap(map, mapWidth, mapHeight);
    }
}

void showLeaf(Leaf *leaf, int level)
{
    for (int i = 0; i < level; i++)
    {
        Logger::log(" ");
    }

    Logger::log("X: (%d - %d), Y(%d - %d)\n",
                leaf->getStartX(),
                leaf->getEndX(),
                leaf->getStartY(),
                leaf->getEndY());

    if (leaf->getLLeaf() != nullptr)
    {
        showLeaf(leaf->getLLeaf(), level + 1);
    }

    if (leaf->getRLeaf() != nullptr)
    {
        showLeaf(leaf->getRLeaf(), level + 1);
    }
}

Map *BSPGenerator::generate(int width, int height)
{
    RandomGenerator generator = RandomGenerator();

    Leaf *rootLeaf = split(0, width, 0, height, splitCount, generator);

    int size = width * height;
    int *map = new int[size];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            *(map + (i * height) + j) = 0;
        }
    }

    showLeaf(rootLeaf, 0);

    leafToMap(rootLeaf, map, width, height);

    return new Map(map, width, height, width / 2, height / 2);
}