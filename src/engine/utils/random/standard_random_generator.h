#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <random>
#include <ctime>

class StandardRandomGenerator
{
public:
    StandardRandomGenerator(int seed)
    {
        srand(seed);
    }

    StandardRandomGenerator()
    {
        srand(time(0));
    }

    int generateFromRange(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    }
};

#endif