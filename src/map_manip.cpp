#include <list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>
#include <functional>

#include "random.h"
#include "graph.h"
#include "map.h"
#include "map_manip.h"
#include "algorithms.h"

namespace pathfinder {

    void MapManipulator::setHeight(Map& map, Map::Coordinates coords, int height){
        bfsGraphTraversal(map, map.getIndex(coords.col, coords.row), [&](int index, int level){
            if(height > 0)
            {
                auto newHeight = height - (this->rng.getRandom() * level);
                if(newHeight > map.getData()[index])
                    map.getData()[index] = newHeight;
            }
            else
            {
                auto newHeight = height + (this->rng.getRandom() * level);
                if(newHeight < map.getData()[index])
                    map.getData()[index] = newHeight;
            }
        });
    };

    void MapManipulator::affectHeight(Map& map, Map::Coordinates coords, int change){
        bfsGraphTraversal(map, map.getIndex(coords.col, coords.row), [&](int index, int level){
            if(change > 0)
            {
                auto newChange = change - (this->rng.getRandom() * level);
                if(newChange > 0)
                    map.getData()[index] += newChange;
            }
            else
            {
                auto newChange = change + (this->rng.getRandom() * level);
                if(newChange < 0)
                    map.getData()[index] += newChange;
            }
        });
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
