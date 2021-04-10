#pragma once

namespace PATHFINDER
{
    /**
     * @brief A path object provide the interface to a set of paths
     *        with a common starting point
     */
    class Paths
    {
        virtual int GetStart() = 0;
        virtual int GetTargets() = 0;
        virtual std::vector<int> GetPath(int target) = 0;
    };

    class PF_Algoritm
    {
        public:
        /**
         * @brief Finds the shortest weighted paths for a start vertex
         *        to all other vertices in the graph
         * @param graph an DirectedGraph
         * @param start the ID of the vertex to use as start
         * @return a Paths object
         */
        virtual Paths* FindPaths(DirectedGraph* graph, int start) = 0;
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
         * @return a Paths object
         */
        virtual Paths* FindPaths(DirectedGraph* graph, int start) override;

        struct Vertex
        {
            uint32_t distance;
            int32_t predecesor;
        };

    };

    bool operator>(const DijkstrasAlgorithm::Vertex& lhs, const DijkstrasAlgorithm::Vertex& rhs);
    bool operator<(const DijkstrasAlgorithm::Vertex& lhs, const DijkstrasAlgorithm::Vertex& rhs);
}