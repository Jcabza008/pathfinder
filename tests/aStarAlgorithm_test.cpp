#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bits/stdc++.h>
#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "map.h"
#include "algorithms.h"
#include "priority_queue.h"

using namespace pathfinder;

TEST(AStarAlgorithm, findPaths_test0)
{
    std::vector<int> data = {
         1,  1,  1,  0, -1, -2, -3, -5, -2, -1,  0,  0,  0,  0,  1,  2,
         1,  1,  2,  1,  1,  1, -2, -3, -3, -2, -1,  0,  1,  1,  2,  2,
         1,  2,  2,  2,  1,  1, -1, -2, -2, -2, -1,  0,  1,  2,  3,  4,
         1,  2,  3,  2,  1,  0,  0, -1, -1, -1,  0,  0,  1,  2,  4,  5,
         1,  3,  4,  2,  2,  1,  1,  0,  0, -1,  0,  1,  1,  3,  5,  5,
         2,  3,  4,  3,  2,  2,  1,  0,  0,  0,  0,  2,  2,  4,  5,  4,
         2,  4,  5,  5,  3,  2,  1,  1,  0,  0,  1,  2,  3,  5,  5,  3,
         2,  2,  4,  5,  5,  3,  2,  1,  0,  0,  2,  3,  5,  5,  4,  3,
         1,  2,  3,  4,  5,  4,  3,  1,  1,  1,  1,  2,  5,  4,  3,  2,
         1,  1,  2,  4,  4,  3,  2,  2,  2,  2,  3, 12,  4,  4,  2,  2,
         0,  1,  2,  3,  3,  2,  2,  3,  4,  3,  2,  2,  3,  3,  2,  1,
         0,  1,  1,  2,  2,  1,  1,  2,  3,  2,  1,  2,  2,  2,  1,  1,
         0,  0,  1,  2,  1,  1,  1,  1,  2,  1,  1,  2,  2,  1,  1,  0,
        -1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  2,  1,  1,  0,  0,
        -1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,
        -2, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    Map map(data, Map::Dimensions({16, 16}));
    AStarAlgorithm aStar;

    auto result = aStar.findPaths(map, map.getIndex(0, 0), map.getIndex(2, 0));

    ASSERT_EQ(result[map.getIndex(2, 0)].cost, 2);
}

TEST(AStarAlgorithm, findPaths_test1)
{
    std::vector<int> data = {
         1,  1,  1,
         1,  1,  2,
         1,  2,  2,
         1,  2,  3,
         1,  3,  4,
        -2, -1,  0
    };

    Map map(data, Map::Dimensions({3, 6}));
    AStarAlgorithm aStar;

    auto result = aStar.findPaths(map, map.getIndex(0, 0), map.getIndex(2, 4));

    ASSERT_EQ(result[map.getIndex(2, 4)].cost, 7);
}

TEST(AStarAlgorithm, findPaths_test2)
{
    std::vector<int> data = {
         1,  1,  1,
         1,  1,  2,
        -1, -1, -1,
         1,  2,  3,
         1,  3,  4,
        -2, -1,  0
    };

    Map map(data, Map::Dimensions({3, 6}));
    AStarAlgorithm aStar;

    auto result = aStar.findPaths(map, map.getIndex(0, 0), map.getIndex(2, 4));

    ASSERT_TRUE(result.empty());
    ASSERT_TRUE(aStar.backtrack(result, map.getIndex(2, 4)).empty());
}

TEST(AStarAlgorithm, findPaths_test3)
{
    std::vector<int> data = {
        50,  30,  5,  1,  1, -1,  -2,  -1,  1, 20,
        50,  30,  2,  1,  1, -1,  -2,  -1, -1,  1,
        40,  30, 20, -1, -1, -1,  -2,  -1,  1,  1,
        40,  30,  3,  1, -1, -1,  -2,  -1,  1,  1,
        40,  30,  4,  1, -1, -1,  -2,  -1,  1,  1,
        40,  30,  0, -1, -1, -1,  -2,  -1,  1,  1
    };

    Map map(data, Map::Dimensions({10, 6}));
    AStarAlgorithm aStar;

    auto result = aStar.findPaths(map, map.getIndex(0, 2), map.getIndex(0, 8));

    ASSERT_TRUE(result.empty());
    ASSERT_TRUE(aStar.backtrack(result, map.getIndex(0, 8)).empty());
}