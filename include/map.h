#pragma once

namespace pathfinder {

    constexpr int c_Max_Traversable_Slope = 10;
    constexpr int c_Negative_Slope_Weight_Correction = 2;

    class Map : public Graph
    {
        public:
        struct Dimensions
        {
            unsigned int width;
            unsigned int height;
        };

        struct Coordinates
        {
            unsigned int col;
            unsigned int row;
        };

        Map(Dimensions dim);
        Map(std::vector<int> data, Dimensions dim);

        Dimensions getDimensions();
        std::vector<int>& getData();
        std::vector<int> getVertices() override;
        std::vector<Target> getAdjecent(int index) override;

        private:
        unsigned int size();
        unsigned int getIndex(unsigned int col, unsigned int row);
        Coordinates getCoords(int index);
        bool validCoord(Coordinates coords);
        std::vector<Coordinates> getNeighbors(int index);
        std::vector<Coordinates> getNeighbors(Coordinates coords);
        int getWeight(Coordinates start, Coordinates target);

        Dimensions dimensions;
        std::vector<int> data;
    };

}

