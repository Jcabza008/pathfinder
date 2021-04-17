#include <bits/stdc++.h>
#include <functional>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "priority_queue.h"
#include "algorithms.h"

namespace pathfinder {

    bool operator==(const PathData& lhs, const PathData& rhs)
    {
        return lhs.cost == rhs.cost && lhs.predecesor == rhs.predecesor;
    }

    std::unordered_map<int, PathData> DijkstrasAlgorithm::findPaths(Graph& graph, int start)
    {
        auto vertices = graph.getVertices();
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, PathData> paths;
        PriorityQueue<VertexData> queue(
            [](VertexData lhs, VertexData rhs){
                return lhs.data->cost < rhs.data->cost;
            });

        for(auto it = vertices.cbegin(); it != vertices.cend(); it++)
        {
            auto cost = INT_MAX;
            if(*it == start)
                cost = 0;

            paths.insert({*it, PathData{cost, -1}});
            queue.push({*it, &paths[*it]});
        }

        while(!queue.empty())
        {
            queue.reorder();
            auto vertex = queue.top();
            queue.pop();
            visited[vertex.index] = true;

            auto neighbors = graph.getAdjecent(vertex.index);
            for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
            {
                if(visited[it->to])
                    continue;

                if(vertex.data->cost + it->weight < paths[it->to].cost)
                {
                    paths[it->to].cost = vertex.data->cost + it->weight;
                    paths[it->to].predecesor = vertex.index;
                }
            }
        }

        return paths;
    }

    void bfsGraphTraversal(Graph& graph, int start, std::function<void(int index, int level)> action)
    {
        std::unordered_map<int, bool> visited;
        std::queue<std::pair<int, int>> q;

        visited[start] = true;
        q.push({start, 0});

        while(!q.empty())
        {
            auto curr = q.front();
            q.pop();
            action(curr.first, curr.second);
            visited[curr.first] = true;

            auto neighbors = graph.getAdjecent(curr.first);
            for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
            {
                if(!visited[it->to])
                    q.push({it->to, curr.second + 1});
            }
        }

    }


}