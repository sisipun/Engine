#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <random>
#include <ctime>

class RandomGenerator
{
public:
    RandomGenerator(int seed)
    {
        srand(seed);
    }

    RandomGenerator()
    {
        srand(time(0));
    }

    int generateFromRange(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    }
};

#endif