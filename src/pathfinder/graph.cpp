#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

#include "graph.h"

namespace PATHFINDER
{
    DirectedGraphLinkedListImpl::DirectedGraphLinkedListImpl(std::vector<DirectedEdge> edges)
    {
        for(auto it = edges.cbegin(); it != edges.cend(); it++)
        {
            this->addEdge(it->from, it->to, it->weight);
        }
    }

    void DirectedGraphLinkedListImpl::addVertex(int id)
    {
        this->getOrCreateVertex(id);
    }

    void DirectedGraphLinkedListImpl::addEdge(int from, int to, int weight)
    {
        auto vertex = this->getOrCreateVertex(from);
        auto target = this->findTarget(vertex->second, to);

        if(target != vertex->second.end())
            target->weight = weight;
        else
            vertex->second.push_back({to, weight});
    }

    void DirectedGraphLinkedListImpl::removeVertex(int id)
    {
        auto vertex = this->getOrCreateVertex(id);
        this->index.erase(vertex);
    }

    void DirectedGraphLinkedListImpl::removeEdge(int from, int to)
    {
        auto vertex = this->getOrCreateVertex(from);
        auto target = this->findTarget(vertex->second, to);
        if(target != vertex->second.end())
            vertex->second.erase(target);
    }

    std::vector<Target> DirectedGraphLinkedListImpl::getAdjecent(int id)
    {
        std::vector<Target> result;
        auto vertex = this->getOrCreateVertex(id);
        for(auto it = vertex->second.cbegin(); it != vertex->second.cend(); it++)
            result.push_back(*it);
        return result;
    }

    std::unordered_map<int, std::list<PATHFINDER::Target>>::iterator DirectedGraphLinkedListImpl::getOrCreateVertex(int id)
    {
        auto vertex = this->index.find(id);
        if(vertex == this->index.end())
        {
            this->index.insert({id, {}});
        }
        return vertex;
    }

    std::_List_iterator<PATHFINDER::Target> DirectedGraphLinkedListImpl::findTarget(std::list<Target> list, int to)
    {
        for(auto it = list.begin(); it != list.end(); it++)
        {
            if(it->to == to)
            {
                return it;
            }
        }
        return list.end();
    }
}