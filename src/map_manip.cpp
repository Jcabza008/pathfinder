#include <list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>

#include "random.h"
#include "graph.h"
#include "map.h"
#include "map_manip.h"

namespace pathfinder {

    void MapManipulator::setHeight(Map& mp, Map::Coordinates coords, int height){

    };

    void MapManipulator::affectHeight(Map& mp, Map::Coordinates coords, int change){

    };

    void MapRandomManipulator::generateRandomFeatures(Map& map, RandomIntGenerator& widthCoordGenerator, RandomIntGenerator& heightCoordGenerator)
    {
        auto featuresCount = this->featuresCountGenerator.getRandom();
        for(int i = 0; i < featuresCount; i++)
        {
            auto coords = Map::Coordinates({static_cast<unsigned int>(widthCoordGenerator.getRandom()),
                                            static_cast<unsigned int>(heightCoordGenerator.getRandom())});
            auto height = this->featuresElevationGenerator.getRandom();
            this->mapManip.setHeight(map, coords, height);
        }
    }

}
