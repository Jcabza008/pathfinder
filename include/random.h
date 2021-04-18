#pragma once

namespace pathfinder {

    class RandomIntGenerator
    {
        public:
        virtual ~RandomIntGenerator() {};
        virtual int getRandom() = 0;
    };

    class RandomUniformIntGenerator : public RandomIntGenerator
    {
        public:
        RandomUniformIntGenerator(int min, int max);
        int getRandom() override;

        private:
        std::uniform_int_distribution<int> distribution;
        static std::random_device rd;
        static std::mt19937 rng;
    };

    class RandomNormalIntGenerator : public RandomIntGenerator
    {
        public:
        RandomNormalIntGenerator(double average, double std);
        int getRandom() override;

        private:
        std::normal_distribution<double> distribution;
        static std::random_device rd;
        static std::mt19937 rng;
    };

}