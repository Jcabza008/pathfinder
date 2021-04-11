#pragma once

namespace PATHFINDER
{
    struct PathData
    {
        int cost;
        int predecesor;
    };

    bool operator==(const PathData& lhs, const PathData& rhs);

    class PF_Algoritm
    {
        public:
        /**
         * @brief Finds the shortest weighted paths for a start vertex
         *        to all other vertices in the graph
         * @param graph an DirectedGraph
         * @param start the ID of the vertex to use as start
         * @return a map from the vertices to the cost and predecesors
         */
        virtual std::unordered_map<int, PathData> findPaths(DirectedGraph* graph, int start) = 0;
    };

    class DijkstrasAlgorithm : PF_Algoritm
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
        virtual std::unordered_map<int, PathData> findPaths(DirectedGraph* graph, int start) override;

        private:
        struct VertexData
        {
            int index;
            PathData* data;
        };
    };
}