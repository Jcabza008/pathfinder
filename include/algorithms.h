#pragma once

namespace pathfinder {

    struct PathData
    {
        int cost;
        int predecesor;
    };

    bool operator==(const PathData& lhs, const PathData& rhs);

    class DijkstrasAlgorithm
    {
        public:
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
        std::unordered_map<int, PathData> findPaths(Graph* graph, int start) override;
        std::vector<int> backtrack(std::unordered_map<int, PathData> pathData, int target);

        private:
        struct VertexData
        {
            int index;
            PathData* data;
        };
    };


    class AStarAlgorithm
    {
        AStarAlgorithm() {};

        std::unordered_map<int, PathData> findPaths(Map& map, int start) override;

        private:
        int heuristic();
        struct VertexData
        {
            int index;
            int fScore;
            PathData* data;
        }
    }

    std::vector<int> aStarBacktrack(std::unordered_map<int, PathData> pathData, int target);



}