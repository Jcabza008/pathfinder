#include <random>

#include "random.h"

namespace pathfinder {

    std::random_device RandomUniformIntGenerator::rd;
    std::mt19937 RandomUniformIntGenerator::rng{RandomUniformIntGenerator::rd()};

    std::random_device RandomNormalIntGenerator::rd;
    std::mt19937 RandomNormalIntGenerator::rng{RandomNormalIntGenerator::rd()};

    RandomUniformIntGenerator::RandomUniformIntGenerator(int min, int max)
    {
        this->distribution = std::uniform_int_distribution<int>(min, max);
    }

    int RandomUniformIntGenerator::getRandom()
    {
        return this->distribution(this->rng);
    }

    RandomNormalIntGenerator::RandomNormalIntGenerator(double average, double std)
    {
        this->distribution = std::normal_distribution<double>(average, std);
    }

    int RandomNormalIntGenerator::getRandom()
    {
        return static_cast<int>(this->distribution(this->rng));
    }

}