#include "bsp_generator.h"

const int RESPLIT_ATTEMPT_COUNT = 100;

Leaf *split(int startX, int endX, int startY, int endY, int splitCount, float ratio, RandomGenerator generator)
{
    if (splitCount <= 0)
    {
        return nullptr;
    }

    int width = endX - startX;
    int height = endY - startY;
    Leaf *lLeaf, *rLeaf = nullptr;

    int attemtCount = 0;
    while (attemtCount < RESPLIT_ATTEMPT_COUNT)
    {
        int splitDirection = generator.generateFromRange(0, 1);
        if (splitDirection == 0)
        {
            int splitX = generator.generateFromRange(width / 3, 2 * width / 3);
            float lLeafRatio = static_cast<float>(splitX) / height;
            float rLeafRatio = static_cast<float>(width - splitX) / height;
            if ((lLeafRatio > ratio && rLeafRatio > ratio))
            {
                lLeaf = split(startX, startX + splitX, startY, endY, splitCount - 1, ratio, generator);
                rLeaf = split(startX + splitX, endX, startY, endY, splitCount - 1, ratio, generator);
                break;
            }
        }
        else
        {
            int splitY = generator.generateFromRange(height / 3, 2 * height / 3);
            float lLeafRatio = static_cast<float>(splitY) / width;
            float rLeafRatio = static_cast<float>(height - splitY) / width;
            if ((lLeafRatio > ratio && rLeafRatio > ratio))
            {
                lLeaf = split(startX, endX, startY, startY + splitY, splitCount - 1, ratio, generator);
                rLeaf = split(startX, endX, startY + splitY, endY, splitCount - 1, ratio, generator);
                break;
            }
        }
        attemtCount++;
    }

    return new Leaf(
        lLeaf,
        rLeaf,
        startX,
        endX,
        startY,
        endY);
}

void leafToMap(Leaf *leaf, int *map, int mapWidth, int mapHeight, RandomGenerator generator)
{
    if (leaf->getLLeaf() != nullptr && leaf->getRLeaf() != nullptr)
    {
        MapGeneratorUtils::squareToMap(
            leaf->getLLeaf()->getStartX() + (leaf->getLLeaf()->getEndX() - leaf->getLLeaf()->getStartX()) / 2,
            leaf->getRLeaf()->getStartX() + (leaf->getRLeaf()->getEndX() - leaf->getRLeaf()->getStartX()) / 2,
            leaf->getLLeaf()->getStartY() + (leaf->getLLeaf()->getEndY() - leaf->getLLeaf()->getStartY()) / 2,
            leaf->getRLeaf()->getStartY() + (leaf->getRLeaf()->getEndY() - leaf->getRLeaf()->getStartY()) / 2,
            map,
            mapWidth,
            mapHeight,
            0);
        leafToMap(leaf->getLLeaf(), map, mapWidth, mapHeight, generator);
        leafToMap(leaf->getRLeaf(), map, mapWidth, mapHeight, generator);
    }
    else
    {
        int leafWidth = leaf->getEndX() - leaf->getStartX();
        int leafHeight = leaf->getEndY() - leaf->getStartY();
        MapGeneratorUtils::boxToMap(
            leaf->getStartX() + generator.generateFromRange(0, leafWidth / 3),
            leaf->getEndX() - generator.generateFromRange(0, leafWidth / 3),
            leaf->getStartY() + generator.generateFromRange(0, leafHeight / 3),
            leaf->getEndY() - generator.generateFromRange(0, leafHeight / 3),
            map,
            mapWidth,
            mapHeight,
            0);
    }
}

Map *BSPGenerator::generate(int width, int height, int splitCount, float ratio, RandomGenerator generator)
{
    Leaf *rootLeaf = split(0, width, 0, height, splitCount, ratio, generator);

    int size = width * height;
    int *map = new int[size];
    MapGeneratorUtils::boxToMap(0, width - 1, 0, height - 1, map, width, height, 1);

    leafToMap(rootLeaf, map, width, height, generator);

    return new Map(map, width, height, width / 2, height / 2);
}