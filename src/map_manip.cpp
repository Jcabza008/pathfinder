#include <list>
#include <queue>
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

    void MapManipulator::setHeight(Map* map, Map::Coordinates coords, int height){
        bfsMapTraversal(map, static_cast<int>(map->getIndex(coords.col, coords.row)), [&](int index, int level){
            if(height > 0)
            {
                auto newHeight = height - (this->rng->getRandom() * level);
                if(newHeight < 0 || newHeight < map->getData()[index])
                    return false;

                map->setData(index, newHeight);
            }
            else
            {
                auto newHeight = height + (this->rng->getRandom() * level);
                if(newHeight > 0 || newHeight > map->getData()[index])
                    return false;

                map->setData(index, newHeight);
            }
            return true;
        });
    };

    void MapManipulator::affectHeight(Map* map, Map::Coordinates coords, int change){
        bfsMapTraversal(map, static_cast<int>(map->getIndex(coords.col, coords.row)), [&](int index, int level){
            if(change > 0)
            {
                auto newChange = change - (this->rng->getRandom() * level);
                if(newChange < 0)
                    return false;

                map->setData(index, map->getData()[index] + newChange);
            }
            else
            {
                auto newChange = change + (this->rng->getRandom() * level);
                if(newChange > 0)
                    return false;

                map->setData(index, map->getData()[index] + newChange);
            }
            return true;
        });
    };

    void MapManipulator::blur(Map* map)
    {
        for(size_t i = 0; i < map->size(); i++)
        {
            double sum = static_cast<double>(map->getData()[i]);
            auto neighbors = map->getNeighbors(i);
            for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
            {
                sum += static_cast<double>(map->getData()[map->getIndex(it->col, it->row)]) * 0.1;
            }
            map->setData(i, static_cast<int>(sum / (1 + (neighbors.size() * 0.15))));
        }
    }

    void MapRandomManipulator::generateRandomFeatures(Map* map, RandomIntGenerator* widthCoordGenerator, RandomIntGenerator* heightCoordGenerator)
    {
        auto featuresCount = this->featuresCountGenerator->getRandom();
        for(int i = 0; i < featuresCount; i++)
        {
            auto coords = Map::Coordinates({static_cast<unsigned int>(widthCoordGenerator->getRandom()),
                                            static_cast<unsigned int>(heightCoordGenerator->getRandom())});
            auto height = this->featuresElevationGenerator->getRandom();
            this->mapManip->setHeight(map, coords, height);
        }
    }


    void bfsMapTraversal(Map* map, int start, std::function<bool(int index, int level)> action)
    {
        std::unordered_map<unsigned int, bool> visited;
        std::queue<std::pair<int, int>> q;

        visited[start] = true;
        q.push({start, 0});

        while(!q.empty())
        {
            auto curr = q.front();
            q.pop();
            auto keepGoing = action(curr.first, curr.second);

            if(keepGoing)
            {
                auto neighbors = map->getNeighbors(curr.first);
                for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
                {
                    if(!visited[map->getIndex(it->col, it->row)])
                    {
                        q.push({map->getIndex(it->col, it->row), curr.second + 1});
                        visited[map->getIndex(it->col, it->row)] = true;
                    }
                }
            }
        }

    }

}
