#pragma once

namespace pathfinder
{
    /**
     * @brief Target describes an endpoint and a weight
     */
    struct Target {
        int to;
        int weight;
    };

    /**
     * @brief Edge is a Target with a starting point
     */
    struct Edge : public Target {
        int from;
    };

    /**
     * @brief Abstract class that defined the interface of a graph
     */
    class Graph
    {
        public:
        /**
         * @brief Get a list of vertices
         * @return std::vector<int> list of vetices
         */
        virtual std::vector<int> getVertices() = 0;

        /**
         * @brief Get the adjecent vertices
         * @param id vertex id
         * @return vector of ids of adjecent vertices
         */
        virtual std::vector<Target> getAdjecent(int index) = 0;
    };

    /**
     * @brief Implementation of a directed graph using a linked list
     */
    class DirectedGraphLinkedListImpl : public Graph
    {
        public:
        /**
         * @brief Directed Graph Linked List Impl default constructor
         */
        DirectedGraphLinkedListImpl() {}

        /**
         * @brief Construct a new Directed Graph Linked List Impl object
         *        from a list of edges. If the desired graph contains a
         *        vertex that is niether the start or target of an edge,
         *        that vertex is not going to be created.
         * @param edges
         */
        DirectedGraphLinkedListImpl(std::vector<Edge> edges);

        /**
         * @brief Construct a new Directed Graph Linked List Impl object
         *        from a list of vertices and a list of edges.
         * @param vertices
         * @param edges
         */
        DirectedGraphLinkedListImpl(std::vector<int> vertices, std::vector<Edge> edges = {});

        /**
         * @brief Adds a vertex to the graph
         * @param id integer that uniquely identifies this vertex
         */
        void addVertex(int id);

        /**
         * @brief Adds an edge to the graph. If any of the two endpoint in the
         *        graph does not exist we create it.
         * @param from id of starting vertex
         * @param to id of target vertex
         * @param weight weight of edge
         */
        void addEdge(int from, int to, int weight);

        /**
         * @brief Removed the vertex with the indicated id
         * @param id the id of vertex to be removed
         */
        void removeVertex(int id);

        /**
         * @brief Removes an edge from the graph
         * @param from starting vertex
         * @param to target vertex
         */
        void removeEdge(int from, int to);

        /**
         * @brief Get a list of vertices
         * @return std::vector<int> list of vetices
         */
        std::vector<int> getVertices() override;

        /**
         * @brief Get the adjecent vertices
         * @param id vertex id
         * @return vector of ids of adjecent vertices
         */
        std::vector<Target> getAdjecent(int id) override;

        private:
        std::unordered_map<int, std::list<Target>>::iterator getVertex(int id, bool create = false);
        std::_List_iterator<Target> findTarget(std::list<Target>& list, int to);

        std::unordered_map<int, std::list<Target>> index;
    };

    bool operator==(const Target& lhs, const Target& rhs);
    bool operator<(const Target& lhs, const Target& rhs);

    bool operator==(const Edge& lhs, const Edge& rhs);
    bool operator<(const Edge& lhs, const Edge& rhs);
}
