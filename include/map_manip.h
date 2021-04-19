#pragma once

namespace pathfinder{

    class MapManipulator
    {
        public:
        MapManipulator(RandomIntGenerator& _rng) : rng(_rng) {}
        void setHeight(Map& map, Map::Coordinates coords, int height);
        void affectHeight(Map& map, Map::Coordinates coords, int factor);
        void blur(Map& map);

        private:

        RandomIntGenerator& rng;
    };

    class MapRandomManipulator
    {
        public:
        MapRandomManipulator(MapManipulator& _mapManip, RandomIntGenerator& _featuresCountGenerator, RandomIntGenerator& _featuresElevationGenerator)
         : mapManip(_mapManip), featuresCountGenerator(_featuresCountGenerator), featuresElevationGenerator(_featuresElevationGenerator) {}

        void generateRandomFeatures(Map& map, RandomIntGenerator& widthCoordGenerator, RandomIntGenerator& heightCoordGenerator);

        std::function<void()> on_Manipulated = []() {};

        private:
        MapManipulator& mapManip;
        RandomIntGenerator& featuresCountGenerator;
        RandomIntGenerator& featuresElevationGenerator;
    };

    void bfsMapTraversal(Map& graph, int start, std::function<bool(int index, int level)> action);

}