#pragma once

namespace pathfinder {

    class DijkstrasAlgorithm
    {
        public:
        struct PathData
        {
            int cost;
            int predecesor;
        };

        struct VertexData
        {
            int index;
            PathData* data;
        };

        /**
         * @brief Default constructor does nothing
         */
        DijkstrasAlgorithm() {};

        /**
         * @brief Finds the shortest weighted paths for a start vertex
         *        to all other vertices in the graph
         * @param graph an DirectedGraph
         * @param start the ID of the vertex to use as start
         * @return a map from the vertices to the cost and predecesors
         */
        std::unordered_map<int, PathData> findPaths(Graph& graph, int src, int target);
        std::vector<int> backtrack(std::unordered_map<int, PathData> pathData, int src, int target);
    };

    bool operator==(const DijkstrasAlgorithm::PathData& lhs, const DijkstrasAlgorithm::PathData& rhs);
    bool operator==(const DijkstrasAlgorithm::VertexData& lhs, const DijkstrasAlgorithm::VertexData& rhs);

    class AStarAlgorithm
    {
        public:
        struct PathData
        {
            int cost;
            int fScore;
            int predecesor;
        };

        struct VertexData
        {
            int index;
            PathData* data;
        };

        AStarAlgorithm() {};

        std::unordered_map<int, PathData> findPaths(Map& map, int start, int target);
        std::vector<int> backtrack(std::unordered_map<int, PathData> pathData, int target);

        private:
        int heuristic(const Map::Coordinates& src, const Map::Coordinates& target);
    };

    bool operator==(const AStarAlgorithm::PathData& lhs, const AStarAlgorithm::PathData& rhs);
    bool operator==(const AStarAlgorithm::VertexData& lhs, const AStarAlgorithm::VertexData& rhs);

}

namespace std {
    template<> struct hash<pathfinder::DijkstrasAlgorithm::VertexData>
    {
        size_t operator()(const pathfinder::DijkstrasAlgorithm::VertexData& vertexData) const
        {
            return std::hash<int>()(vertexData.index);
        }
    };

    template<> struct hash<pathfinder::AStarAlgorithm::VertexData>
    {
        size_t operator()(const pathfinder::AStarAlgorithm::VertexData& vertexData) const
        {
            return std::hash<int>()(vertexData.index);
        }
    };
}