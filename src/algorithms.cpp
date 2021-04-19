#include <bits/stdc++.h>
#include <functional>
#include <list>
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

    std::unordered_map<int, PathData> DijkstrasAlgorithm::findPaths(Graph* graph, int start)
    {
        auto vertices = graph->getVertices();
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

            auto neighbors = graph->getAdjecent(vertex.index);
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

    std::vector<int> dijkstrasBacktrack(std::unordered_map<int, PathData> pathData, int target)
    {
        std::vector<int> result;
        std::stack<int> s;
        s.push(target);
        auto current = target;

        while (pathData[current].predecesor != -1)
        {
            current = pathData[current].predecesor;
            s.push(current);
        }

        while(!s.empty())
        {
            auto current = s.top();
            s.pop();
            result.push_back(current);
        }

        return result;
    }

    int AStarAlgorithm::heuristic(Graph* graph){
        /* One option is to calculate linear distance from someNeighbor to end */
        int start = graph->getVertices()[(int)startPos];
        int end = graph->getVertices()[(int)targetPos];
        /* Consider also the manhattan approach since we have 8-way movement */
    }
    
    const int& heuristic(const int & xDest, const int & yDest) const
    {
        int xd, yd, d;
        xd=xDest-start;
        yd=yDest-start;         

        // Euclidian Distance
        d = static_cast<int>(std::sqrt(xd*xd + yd*yd));

        // Manhattan distance
        //d=abs(xd)+abs(yd);
        
        // Chebyshev distance
        //d=max(abs(xd), abs(yd));

        return d;
    }
    
    std::unordered_map<int, PathData> AStarAlgorithm::findPaths(Graph* graph, int start)
    {
        auto vertices = graph->getVertices();
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

            auto neighbors = graph->getAdjecent(vertex.index);
            for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
            {
                if(visited[it->to])
                    continue;

                //https://github.com/daancode/a-star/blob/master/source/AStar.cpp
                if(vertex.data->cost + heuristic(graph) < paths[it->to].cost)
                {
                    paths[it->to].cost = vertex.data->cost + it->weight;
                    paths[it->to].predecesor = vertex.index;
                }
            }
        }
        return paths;
    }



}