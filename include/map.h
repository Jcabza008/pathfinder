#pragma once

namespace pathfinder{
    struct Dimensions{
        unsigned int xMax;
        unsigned int yMax;
        unsigned int size;
    };
    class Map{
        private:
            Dimensions dimensions;
            int *arr;

        public:
            Map();
            Map(unsigned int x, unsigned int y);

            int getHeight();
    };
}

