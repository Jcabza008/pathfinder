#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

#include "log.h"
#include "graph.h"

#include "map.h"

namespace pathfinder {

    Map::Map(Dimensions dim) : dimensions(dim)
    {
        this->data = std::vector<int>(this->size(), 0);
    };

    Map::Map(vector<int> _data, Dimensions dim) : dimensions(dim), data(_data) {}

    Map::Dimensions Map::getDimensions()
    {
        return this->dimensions;
    }

    std::vector<int> Map::getData()
    {
        return this->data;
    }

    std::vector<int> Map::getVertices()
    {
        std::vector<int> vertices;
        for(size_t i = 0; i < this->size(); i++)
            vertices.push_back(i);

        return vertices;
    }

    std::vector<Target> Map::getAdjecent(int index)
    {
        std::vector<Target> result;
        auto neighbors = this->getNeighbors(index);

        for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
        {
            auto weight = getWeight(this->getCoords(index), *it);
            if(weight >= 0)
            {
                result.push_back(Target({this->getIndex(*it), weight}));
            }
        }

        return result;
    }

    int Map::size()
    {
        return this->dimensions.width * this->dimensions.height;
    }

    std::vector<Coordinates> Map::getNeighbors(int index)
    {
        return this->getNeighbors(this->getCoords(index));
    }

    std::vector<Coordinates> Map::getNeighbors(Coordinates coords)
    {
        std::vector<Coordinates> neighbors;
        int row = coords.row;
		int col = coords.col;

		neighbors.push_back(Coordinates({row - 1, col - 1})); // upleft
        neighbors.push_back(Coordinates({row - 1, col    })); // up
        neighbors.push_back(Coordinates({row - 1, col + 1})); // upright
        neighbors.push_back(Coordinates({row    , col - 1})); // left
        neighbors.push_back(Coordinates({row    , col + 1})); // right
        neighbors.push_back(Coordinates({row + 1, col - 1})); // downleft
        neighbors.push_back(Coordinates({row + 1, col    })); // down
        neighbors.push_back(Coordinates({row + 1, col + 1})); // downright

        for(auto it = neighbors.begin(); it != neighbors.end(); it++)
        {
            if(!validCoord(*it))
                neighbors.erase(it);
        }

        return neighbors;
    }

    int Map::getIndex(int col, int row)
    {
        return row * this->dimensions.width + col;
    }

    Map::Coordinates Map::getCoords(int index)
    {
        return Coordinates({index % this->dimensions.width, index / this->dimensions.width});
    }

    bool Map::validCoord(Coordinate coords)
    {
        if (coords.row < 0 || coords.col < 0 || coords.row >= this->dimensions.height || coords.col >= this->dimensions.width)
			return false;

        return true;
    }

    int Map::getWeight(Coords start, Coords target)
    {
        auto startHeight = this->data[this->getIndex(start)];
        auto targetHeight = this->data[this->getIndex(target)];

        if(targetHeight < 0 || startHeight < 0) // Water is unaccessible
            return -1;

        if(std::abs(targetHeight - startHeight) > c_Max_Traversable_Slope) // Slope is grater than the max traversable
            return -1;

        if(targetHeight - startHeight < 0) // Negative slope
            return (startHeight - targetHeight) * c_Negative_Slope_Weight_Correction;

        return targetHeight - startHeight;
    }

}
