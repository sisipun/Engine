#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <random>
#include <ctime>

class RandomGenerator
{
public:
    RandomGenerator()
    {
    }

    int generateFromRange(int from, int to)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(from, to);
        return distribution(generator);
    }
};

#endif