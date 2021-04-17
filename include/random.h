#pragma once

namespace pathfinder {

    class RandomIntGenerator
    {
        virtual int getRandom() = 0;
    };

    class RandomIntGeneratorMT19937 : public RandomIntGenerator
    {
        public:
        RandomIntGeneratorMT19937(int min, int max);
        int getRandom() override;

        private:
        std::uniform_int_distribution<int> uid;
        static std::random_device rd;
        static std::mt19937 rng;
    };

}