#ifndef BSP_GENERATOR_H
#define BSP_GENERATOR_H

#include "map_generator.h"

class BSPGenerator : public MapGenerator
{
public:
    BSPGenerator(int splitCount = 4) : splitCount(splitCount)
    {
    }

    Map *generate(int width, int height) override;

private:
    int splitCount;
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

    Leaf *getLLeaf() {
        return lLeaf;
    }

    Leaf *getRLeaf() {
        return rLeaf;
    }

    int getStartX() {
        return startX;
    }

    int getEndX() {
        return endX;
    }

    int getStartY() {
        return startY;
    }

    int getEndY() {
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