#include "bsp_generator.h"
#include "../random/random_generator.h"
#include "../logger/logger.h"

const int RESPLIT_ATTEMPT_COUNT = 100;
const float RATIO = 0.45;

Leaf *split(int startX, int endX, int startY, int endY, int splitCount, RandomGenerator generator)
{
    if (splitCount <= 0)
    {
        return nullptr;
    }

    int width = endX - startX;
    int height = endY - startY;
    Leaf *lLeaf, *rLeaf = nullptr;

    int attemtCount = 0;
    while (true)
    {
        int splitDirection = generator.generateFromRange(0, 1);
        if (splitDirection == 0)
        {
            int splitX = generator.generateFromRange(width / 3, 2 * width / 3);
            float lLeafRatio = static_cast<float>(splitX) / height;
            float rLeafRatio = static_cast<float>(width - splitX) / height;
            if ((lLeafRatio > RATIO && rLeafRatio > RATIO) || attemtCount >= RESPLIT_ATTEMPT_COUNT)
            {
                lLeaf = split(startX, startX + splitX, startY, endY, splitCount - 1, generator);
                rLeaf = split(startX + splitX, endX, startY, endY, splitCount - 1, generator);
                break;
            }
        }
        else
        {
            int splitY = generator.generateFromRange(height / 3, 2 * height / 3);
            float lLeafRatio = static_cast<float>(splitY) / width;
            float rLeafRatio = static_cast<float>(height - splitY) / width;
            if ((lLeafRatio > RATIO && rLeafRatio > RATIO) || attemtCount >= RESPLIT_ATTEMPT_COUNT)
            {
                lLeaf = split(startX, endX, startY, startY + splitY, splitCount - 1, generator);
                rLeaf = split(startX, endX, startY + splitY, endY, splitCount - 1, generator);
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
        int leftCenterX = leaf->getLLeaf()->getStartX() + (leaf->getLLeaf()->getEndX() - leaf->getLLeaf()->getStartX()) / 2;
        int leftCenterY = leaf->getLLeaf()->getStartY() + (leaf->getLLeaf()->getEndY() - leaf->getLLeaf()->getStartY()) / 2;
        int rightCenterX = leaf->getRLeaf()->getStartX() + (leaf->getRLeaf()->getEndX() - leaf->getRLeaf()->getStartX()) / 2;
        int rightCenterY = leaf->getRLeaf()->getStartY() + (leaf->getRLeaf()->getEndY() - leaf->getRLeaf()->getStartY()) / 2;
        for (int i = leftCenterX; i <= rightCenterX; i++)
        {
            *(map + (i * mapHeight) + leftCenterY) = 0;
            *(map + (i * mapHeight) + rightCenterY) = 0;
        }
        for (int j = leftCenterY; j <= rightCenterY; j++)
        {
            *(map + (leftCenterX * mapHeight) + j) = 0;
            *(map + (rightCenterX * mapHeight) + j) = 0;
        }
        leafToMap(leaf->getLLeaf(), map, mapWidth, mapHeight, generator);
        leafToMap(leaf->getRLeaf(), map, mapWidth, mapHeight, generator);
    }
    else
    {
        int leafWidth = leaf->getEndX() - leaf->getStartX();
        int leafHeight = leaf->getEndY() - leaf->getStartY();
        int leftCrop = generator.generateFromRange(0, leafWidth / 3);
        int rightCrop = generator.generateFromRange(0, leafWidth / 3);
        int bottomCrop = generator.generateFromRange(0, leafHeight / 3);
        int topCrop = generator.generateFromRange(0, leafHeight / 3);
        int startX = leaf->getStartX() + leftCrop;
        int endX = leaf->getEndX() - rightCrop;
        int startY = leaf->getStartY() + bottomCrop;
        int endY = leaf->getEndY() - topCrop;
        for (int i = startX; i < endX; i++)
        {
            for (int j = startY; j < endY; j++)
            {
                *(map + (i * mapHeight) + j) = 0;
            }
        }
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
            *(map + (i * height) + j) = 1;
        }
    }

    leafToMap(rootLeaf, map, width, height, generator);

    return new Map(map, width, height, width / 2, height / 2);
}