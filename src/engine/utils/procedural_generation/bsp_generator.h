#ifndef BSP_GENERATOR_H
#define BSP_GENERATOR_H

#include "map.h"
#include "../random/random_generator.h"

class BSPGenerator
{
public:
    Map *generate(int width, int height, int splitCount = 6, float ratio = 0.45, RandomGenerator generator = RandomGenerator());
};

class Leaf
{
public:
    Leaf(Leaf *lLeaf, Leaf *rLeaf, int startX, int endX, int startY, int endY) : lLeaf(lLeaf),
                                                                                 rLeaf(rLeaf),
                                                                                 startX(startX),
                                                                                 endX(endX),
                                                                                 startY(startY),
                                                                                 endY(endY) {}

    ~Leaf()
    {
        if (lLeaf != nullptr)
        {
            delete lLeaf;
        }
        if (rLeaf != nullptr)
        {
            delete rLeaf;
        }
    }

    Leaf *getLLeaf()
    {
        return lLeaf;
    }

    Leaf *getRLeaf()
    {
        return rLeaf;
    }

    int getStartX()
    {
        return startX;
    }

    int getEndX()
    {
        return endX;
    }

    int getStartY()
    {
        return startY;
    }

    int getEndY()
    {
        return endY;
    }

private:
    Leaf *lLeaf;
    Leaf *rLeaf;
    int startX;
    int endX;
    int startY;
    int endY;
};

#endif