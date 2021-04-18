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
        class Parser
        {
            Map parse(std::istream& input);
            std::ostream deparse(Map& mp, std::string filename);
        };
        struct Coordinates
        {
            unsigned int col;
            unsigned int row;
        };
        Map(Dimensions dim);
        Map(std::vector<int> data, Dimensions dim);

        std::vector<int> getVertices() override;
        std::vector<Target> getAdjecent(int index) override;

        unsigned int size();
        std::vector<int>& getData();
        Dimensions getDimensions();
        Coordinates getCoords(int index);
        unsigned int getIndex(unsigned int col, unsigned int row);
        std::vector<Coordinates> getNeighbors(int index);
        std::vector<Coordinates> getNeighbors(Coordinates coords);

        private:
        bool validCoord(Coordinates coords);
        int getWeight(Coordinates start, Coordinates target);

        Dimensions dimensions;
        std::vector<int> data;
    };

}

