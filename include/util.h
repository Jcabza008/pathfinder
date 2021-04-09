#pragma once

namespace PATHFINDER
{
    /**
     * @brief Checks that two vectors contain the same elements
     *        without taking into account the order
     * @tparam T the type the the vector
     * @param lhs a vector<T>
     * @param rhs a vector<T>
     * @return true the two vectors contain the same elements
     * @return false the two vectors do not contain the same elements
     */
    template <typename T>
    bool equalVectorsUnordered(std::vector<T> lhs, std::vector<T> rhs)
    {
        std::unordered_map<T, int> count;
        for(auto it = lhs.cbegin(); it != lhs.cend(); it++)
            count[*it]++;

        for(auto it = rhs.cbegin(); it != rhs.cend(); it++)
            count[*it]--;

        for(auto it = count.cbegin(); it != count.cend(); it++)
        {
            if(it->second != 0)
                return false;
        }
        return true;
    }
}