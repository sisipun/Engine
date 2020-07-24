#ifndef CELLULAR_AUTOMATA_MAZE_GENERATOR_H
#define CELLULAR_AUTOMATA_MAZE_GENERATOR_H

#include "maze_generator.h"

class CellularAutomataMazeGenerator : public MazeGenerator
{
public:
    CellularAutomataMazeGenerator(int birthLimit = 4, int deathLimit = 3, int initialChance = 50, int stepCount = 4)
    {
        if (birthLimit > 6)
        {
            this->birthLimit = 6;
        }
        else if (birthLimit < 1)
        {
            this->birthLimit = 1;
        }
        else
        {
            this->birthLimit = birthLimit;
        }

        if (deathLimit > 6)
        {
            this->deathLimit = 6;
        }
        else if (deathLimit < 1)
        {
            this->deathLimit = 1;
        }
        else
        {
            this->deathLimit = deathLimit;
        }

        if (initialChance > 100)
        {
            this->initialChance = 100;
        }
        else if (initialChance < 0)
        {
            this->initialChance = 0;
        }
        else
        {
            this->initialChance = initialChance;
        }

        if (stepCount > 10)
        {
            this->stepCount = 10;
        }
        else if (stepCount < 1)
        {
            this->stepCount = 1;
        }
        else
        {
            this->stepCount = stepCount;
        }
    }

    int *generate(int width, int height) override;

private:
    int deathLimit;
    int birthLimit;
    int initialChance;
    int stepCount;
};

#endif