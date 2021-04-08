#pragma once

namespace PATHFINDER
{
    /**
     * @brief Target describes an endpoint and a weight
     */
    struct Target {
        int to;
        int weight;
    };

    /**
     * @brief Directed Edge is a Target with a starting point
     */
    struct DirectedEdge : public Target {
        int from;
    };

    /**
     * @brief Abstract class that defined the interface of a directed graph
     */
    class DirectedGraph
    {
        public:

        /**
         * @brief Adds a vertex to the graph
         * @param id integer that uniquely identifies this vertex
         */
        virtual void addVertex(int id) = 0;

        /**
         * @brief Adds an edge to the graph. If any of the two endpoint in the
         *        graph does not exist we create it.
         * @param from id of starting vertex
         * @param to id of target vertex
         * @param weight weight of edge
         */
        virtual void addEdge(int from, int to, int weight) = 0;

        /**
         * @brief Removed the vertex with the indicated id
         * @param id the id of vertex to be removed
         */
        virtual void removeVertex(int id) = 0;

        /**
         * @brief Removes an edge from the graph
         * @param from starting vertex
         * @param to target vertex
         */
        virtual void removeEdge(int from, int to) = 0;

        /**
         * @brief Get the adjecent vertices
         * @param id vertex id
         * @return vector of ids of adjecent vertices
         */
        virtual std::vector<Target> getAdjecent(int id) = 0;
    };

    /**
     * @brief Implementation of a directed graph using a linked list
     */
    class DirectedGraphLinkedListImpl : public DirectedGraph
    {
        public:
        /**
         * @brief Construct a new Directed Graph Linked List Impl object
         *        from a list of edges. If the desired graph contains a
         *        vertex that is niether the start or target of an edge,
         *        that vertex is not going to be created.
         * @param edges
         */
        DirectedGraphLinkedListImpl(std::vector<DirectedEdge> edges);

        /**
         * @brief Construct a new Directed Graph Linked List Impl object
         *        from a list of vertices and a list of edges.
         * @param vertices
         * @param edges
         */
        DirectedGraphLinkedListImpl(std::vector<int> vertices, std::vector<DirectedEdge> edges);

        /**
         * @brief Adds a vertex to the graph
         * @param id integer that uniquely identifies this vertex
         */
        virtual void addVertex(int id) override;

        /**
         * @brief Adds an edge to the graph. If any of the two endpoint in the
         *        graph does not exist we create it.
         * @param from id of starting vertex
         * @param to id of target vertex
         * @param weight weight of edge
         */
        virtual void addEdge(int from, int to, int weight) override;

        /**
         * @brief Removed the vertex with the indicated id
         * @param id the id of vertex to be removed
         */
        virtual void removeVertex(int id) override;

        /**
         * @brief Removes an edge from the graph
         * @param from starting vertex
         * @param to target vertex
         */
        virtual void removeEdge(int from, int to) override;

        /**
         * @brief Get the adjecent vertices
         * @param id vertex id
         * @return vector of ids of adjecent vertices
         */
        virtual std::vector<Target> getAdjecent(int id) override;

        private:
        std::unordered_map<int, std::list<PATHFINDER::Target>>::iterator getOrCreateVertex(int id);
        std::_List_iterator<PATHFINDER::Target> findTarget(std::list<Target> list, int to);

        std::unordered_map<int, std::list<Target>> index;
    };
}