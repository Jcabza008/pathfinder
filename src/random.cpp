#include <random>

#include "random.h"

namespace pathfinder {

    std::random_device RandomIntGeneratorMT19937::rd;
    std::mt19937 RandomIntGeneratorMT19937::rng{RandomIntGeneratorMT19937::rd()};

    RandomIntGeneratorMT19937::RandomIntGeneratorMT19937(int min, int max)
    {
        this->uid = std::uniform_int_distribution<int>(min, max);
    }

    int RandomIntGeneratorMT19937::getRandom()
    {
        return this->uid(this->rng);
    }

}