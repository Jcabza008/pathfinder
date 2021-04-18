#include <list>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <vector>

#include "map.h"
#include "graph.h"

namespace pathfinder {

    Map::Map(Dimensions dim) : dimensions(dim)
    {
        this->data = std::vector<int>(this->size(), 0);
    };

    Map::Map(std::vector<int> _data, Dimensions dim) : dimensions(dim), data(_data) {}

    Map::Dimensions Map::getDimensions()
    {
        return this->dimensions;
    }

    std::vector<int>& Map::getData()
    {
        return this->data;
    }

    std::vector<int> Map::getVertices()
    {
        std::vector<int> vertices;
        for(size_t i = 0; i < (size_t)this->size(); i++)
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
                result.push_back(Target({static_cast<int>(this->getIndex(it->col, it->row)), weight}));
            }
        }

        return result;
    }

    unsigned int Map::size()
    {
        return this->dimensions.width * this->dimensions.height;
    }

    std::vector<Map::Coordinates> Map::getNeighbors(int index)
    {
        return this->getNeighbors(this->getCoords(index));
    }

    std::vector<Map::Coordinates> Map::getNeighbors(Coordinates coords)
    {
        std::vector<Coordinates> neighbors;
        auto row = coords.row;
		auto col = coords.col;

		neighbors.push_back(Coordinates({col - 1, row - 1})); // upleft
        neighbors.push_back(Coordinates({col    , row - 1})); // up
        neighbors.push_back(Coordinates({col + 1, row - 1})); // upright
        neighbors.push_back(Coordinates({col - 1, row    })); // left
        neighbors.push_back(Coordinates({col + 1, row    })); // right
        neighbors.push_back(Coordinates({col - 1, row + 1})); // downleft
        neighbors.push_back(Coordinates({col    , row + 1})); // down
        neighbors.push_back(Coordinates({col + 1, row + 1})); // downright

        for(auto it = neighbors.begin(); it != neighbors.end(); it++)
        {
            if(!validCoord(*it))
                neighbors.erase(it--);
        }

        return neighbors;
    }

    unsigned int Map::getIndex(unsigned int col, unsigned int row)
    {
        return row * this->dimensions.width + col;
    }

    Map::Coordinates Map::getCoords(int index)
    {
        return Coordinates({index % this->dimensions.width, index / this->dimensions.width});
    }
    
    Map Map::Parser::parse(std::istream& binaryInput){
        binaryInput.seekg(0, binaryInput.end);
        auto fileLength = binaryInput.tellg();
        
        Map::Dimensions d;
        binaryInput >> d.height;
        binaryInput >> d.width;
        int cap = d.width*d.height;
        std::vector<int> data;
        char* buf = new char [fileLength];
        binaryInput.read(buf, fileLength);
        Map map(data, d);
        return map;
    }
    std::ostream& Map::Parser::deparse(Map& map, std::string filename){
        std::filebuf fb;
        std::ostream output();
        output.open(filename);
        for(auto i : map.getData()){
            output << i;
        }
        return output;
    }

    bool Map::validCoord(Coordinates coords)
    {
        if (coords.row >= this->dimensions.height || coords.col >= this->dimensions.width)
			return false;

        return true;
    }

    int Map::getWeight(Coordinates start, Coordinates target)
    {
        auto startHeight = this->data[this->getIndex(start.col, start.row)];
        auto targetHeight = this->data[this->getIndex(target.col, target.row)];

        if(targetHeight < 0 || startHeight < 0) // Water is unaccessible
            return -1;

        if(std::abs(targetHeight - startHeight) > c_Max_Traversable_Slope) // Slope is grater than the max traversable
            return -1;

        if(targetHeight - startHeight < 0) // Negative slope
            return 1 + ((startHeight - targetHeight) / c_Negative_Slope_Weight_Correction);

        return 1 + (targetHeight - startHeight);
    }

}
