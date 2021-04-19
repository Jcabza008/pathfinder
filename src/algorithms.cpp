#include <bits/stdc++.h>
#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "map.h"
#include "priority_queue.h"
#include "algorithms.h"

namespace pathfinder {

    bool operator==(const DijkstrasAlgorithm::PathData& lhs, const DijkstrasAlgorithm::PathData& rhs)
    {
        return lhs.cost == rhs.cost && lhs.predecesor == rhs.predecesor;
    }

    std::unordered_map<int, DijkstrasAlgorithm::PathData> DijkstrasAlgorithm::findPaths(Graph& graph, int src, int target)
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
            if(*it == src)
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
            if(vertex.index == target) { return paths; }

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
        return std::unordered_map<int, PathData>();
    }

    std::vector<int> DijkstrasAlgorithm::backtrack(std::unordered_map<int, PathData> pathData, int src, int target)
    {
        std::vector<int> result;
        std::stack<int> s;
        s.push(target);
        auto current = target;

        if(pathData.empty())
            return result;

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

    int AStarAlgorithm::heuristic(const Map::Coordinates& src, const Map::Coordinates& target)
    {
        return static_cast<int>(std::sqrt(std::pow((target.col - src.col), 2) + std::pow((target.row - src.row), 2)));
    }

    std::unordered_map<int, AStarAlgorithm::PathData> AStarAlgorithm::findPaths(Map& map, int src, int target)
    {
        auto vertices = map.getVertices();
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, PathData> paths;
        PriorityQueue<VertexData> queue(
            [](VertexData lhs, VertexData rhs){
                return lhs.data->fScore < rhs.data->fScore;
            });
        for(auto it = vertices.cbegin(); it != vertices.cend(); it++)
        {
            auto cost = INT_MAX;
            auto fScore = INT_MAX;
            if(*it == src)
            {
                cost = 0;
                fScore = this->heuristic(map.getCoords(src), map.getCoords(target));
            }
            paths.insert({*it, PathData{cost, fScore, -1}});
            visited[*it] = true;
        }
        queue.push({src, &paths[src]});
        visited[src] = false;

        while(!queue.empty())
        {
            queue.reorder();
            auto vertex = queue.top();
            queue.pop();
            if(vertex.index == target){ return paths; } // this backtrack
            visited[vertex.index] = true;

            auto neighbors = map.getAdjecent(vertex.index);
            for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
            {
                auto tentativeCost = vertex.data->cost + it->weight;
                if(tentativeCost < paths[it->to].cost)
                {
                    paths[it->to].predecesor = vertex.index;
                    paths[it->to].cost = tentativeCost;
                    paths[it->to].fScore = tentativeCost + this->heuristic(map.getCoords(it->to), map.getCoords(target));
                    if(visited[it->to])
                    {
                        visited[it->to] = false;
                        queue.push({it->to, &paths[it->to]});
                    }
                }
            }
        }
        return std::unordered_map<int, PathData>();
    }

    std::vector<int> AStarAlgorithm::backtrack(std::unordered_map<int, PathData> pathData, int target)
    {

        std::vector<int> result;
        std::stack<int> s;
        s.push(target);
        auto current = target;

        if(pathData.empty())
            return result;

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
}