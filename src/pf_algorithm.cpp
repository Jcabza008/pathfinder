#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "pf_algoritm.h"
#include "priority_queue.h"

namespace PATHFINDER
{
    Paths* DijkstrasAlgorithm::FindPaths(DirectedGraph* graph, int start)
    {
        auto vertices = graph->getVertices();
        PriorityQueue<DijkstrasAlgorithm::Vertex> queue(vertices.size());
        for(auto it = vertices.cbegin(); it != vertices.cend(); it++)
        {
            if(*it == start)
            {
                queue.push({0, -1});
            }
            else
            {
                queue.push({UINT32_MAX, -1});
            }
        }

        return nullptr;
    }

    bool operator>(const DijkstrasAlgorithm::Vertex& lhs, const DijkstrasAlgorithm::Vertex& rhs)
    {
        return lhs.distance > rhs.distance;
    }

    bool operator<(const DijkstrasAlgorithm::Vertex& lhs, const DijkstrasAlgorithm::Vertex& rhs)
    {
        return lhs.distance < rhs.distance;
    }
}