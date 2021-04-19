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

    std::unordered_map<int, DijkstrasAlgorithm::PathData> DijkstrasAlgorithm::findPaths(Graph* graph, int start)
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

    std::vector<int> DijkstrasAlgorithm::backtrack(std::unordered_map<int, PathData> pathData, int target)
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

    int AStarAlgorithm::heuristic(const Map::Coordinates& src, const Map::Coordinates& end){
        return static_cast<int>(std::sqrt(std::pow((end.col - src.col), 2) + std::pow((end.row - src.row), 2)));
    }
    
    int AStarAlgorithm::calcF(int cost, const Map::Coordinates& src, const Map::Coordinates& end){
        return cost + heuristic(src, end);
    }

    std::unordered_map<int, PathData> AStarAlgorithm::findPaths(Map& map, int start, int end)
    {
        auto vertices = map.getVertices();
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, VertexData> paths;
        PriorityQueue<VertexData> queue(
            [](VertexData lhs, VertexData rhs){
                return lhs.fScore < rhs.fScore;
            });
        for(auto it = vertices.cbegin(); it != vertices.cend(); it++)
        {
            auto cost = INT_MAX;
            if(*it == start)
                cost = 0;
            paths.insert({*it, VertexData{*it,}});
        }
        queue.push({start, calcF(0, map.getCoords(start), map.getCoords(end)), &paths[start]});
        while(!queue.empty())
        {
            queue.reorder();
            auto vertex = queue.top();
            queue.pop();
            if(it->to == end){ return paths; }
            visited[vertex.index] = true;

            auto neighbors = map.getAdjecent(vertex.index);
            for(auto it = neighbors.cbegin(); it != neighbors.cend(); it++)
            {
                auto tentativeCost = vertex.data->cost + it->weight;
                if(tentativeCost < paths[it->to].cost)
                {
                    paths[it->to].predecesor = vertex.index;
                    paths[it->to].cost = tentativeCost;
                    auto f = calcF(tentativeCost, map.getCoords(it->to), map.getCoords(end));
                    queue.push({it->to, f, &paths[it->to]});
                }
                
                if(!visited[it->to] && calcF(paths[it->to].cost, map.getCoords(it->to), map.getCoords(end)))
                {
                    
                }
                if(vertex.data->cost + heuristic() < paths[it->to].cost)
                {
                    paths[it->to].cost = vertex.data->cost + it->weight;
                    paths[it->to].predecesor = vertex.index;
                }
            }
        }
        return paths;
    }



}