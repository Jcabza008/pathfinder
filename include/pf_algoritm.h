#pragma once

namespace pathfinder
{
    class Path
    {
        virtual int GetStart() = 0;
        virtual int GetTarget() = 0;
        virtual std::vector<int> GetPath() = 0;
    }

    class PF_Algoritm
    {
        public:
        virtual std::vector<Path> FindPaths(DirectedGraph graph, int start) = 0;
    };
}