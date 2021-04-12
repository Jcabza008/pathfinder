#pragma once

namespace PATHFINDER
{
    template<typename T>
    class ADTProvider
    {
        T* Get() { return new T; }
    };


}