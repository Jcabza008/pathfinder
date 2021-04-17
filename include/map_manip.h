#pragma once

namespace pathfinder{

    class MapManipulator{
        public:
        MapManipulator(RandomIntGenerator& _rng) : rng(_rng) {}
        void setHeight(Map& map, Map::Coordinates coords, int height);
        void affectHeight(Map& map, Map::Coordinates coords, int factor);

        private:
        RandomIntGenerator& rng;
    };

}