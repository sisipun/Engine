#ifndef DRUNKARD_WALK_MAZE_GENERATOR_H
#define DRUNKARD_WALK_MAZE_GENERATOR_H

#include "map_generator.h"

class DrunkardWalkGenerator : public MapGenerator
{
public:
    DrunkardWalkGenerator(int coverage = 50)
    {
        if (coverage > 100)
        {
            this->coverage = 100;
        }
        else if (coverage < 0)
        {
            this->coverage = 0;
        }
        else
        {
            this->coverage = coverage;
        }
    }

    Map *generate(int width, int height) override;

private:
    int coverage;
};

#endif