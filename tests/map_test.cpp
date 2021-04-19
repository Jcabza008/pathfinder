#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "graph.h"
#include "map.h"
#include "util.h"

using namespace pathfinder;

TEST(Map, getDimensions_Test0)
{
    Map map(Map::Dimensions({10, 20}));
    ASSERT_EQ(map.getDimensions().width, 10);
    ASSERT_EQ(map.getDimensions().height, 20);
}

TEST(Map, getData_Test0)
{
    Map map(Map::Dimensions({10, 20}));
    auto data = map.getData();
    for(auto it = data.cbegin(); it != data.cend(); it++)
    {
        ASSERT_EQ(*it, 0);
    }
}

TEST(Map, getVertices_Test0)
{
    Map map(Map::Dimensions({5, 5}));
    auto vertices = map.getVertices();

    std::vector<int> expected(25);
    for(size_t i = 0; i < expected.size(); i++)
        expected[i] = i;

    ASSERT_EQ(vertices, expected);
}

TEST(Map, getAdjecent_Test0)
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
         1,  1,  2,  4,  4,  3,  2,  2,  2,  2,  3,  3,  4,  4,  2,  2,
         0,  1,  2,  3,  3,  2,  2,  3,  4,  3,  2,  2,  3,  3,  2,  1,
         0,  1,  1,  2,  2,  1,  1,  2,  3,  2,  1,  2,  2,  2,  1,  1,
         0,  0,  1,  2,  1,  1,  1,  1,  2,  1,  1,  2,  2,  1,  1,  0,
        -1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  2,  1,  1,  0,  0,
        -1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,
        -2, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    Map map(data, Map::Dimensions({16, 16}));
    auto adjecent = map.getAdjecent(0);
    ASSERT_TRUE(equalVectorsUnordered(adjecent, std::vector<Target>({{1, 1}, {16, 1}, {17, 1}})));
}

TEST(Map, getAdjecent_Test1)
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
         1,  1,  2,  4,  4,  3,  2,  2,  2,  2,  3,  3,  4,  4,  2,  2,
         0,  1,  2,  3,  3,  2,  2,  3,  4,  3,  2,  2,  3,  3,  2,  1,
         0,  1,  1,  2,  2,  1,  1,  2,  3,  2,  1,  2,  2,  2,  1,  1,
         0,  0,  1,  2,  1,  1,  1,  1,  2,  1,  1,  2,  2,  1,  1,  0,
        -1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  2,  1,  1,  0,  0,
        -1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,
        -2, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    Map map(data, Map::Dimensions({16, 16}));
    auto adjecent = map.getAdjecent(23);
    ASSERT_TRUE(equalVectorsUnordered(adjecent, std::vector<Target>({})));
}

TEST(Map, getAdjecent_Test2)
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
         1,  1,  2,  4,  4,  3,  2,  2,  2,  2,  3,  3,  4,  4,  2,  2,
         0,  1,  2,  3,  3,  2,  2,  3,  4,  3,  2,  2,  3,  3,  2,  1,
         0,  1,  1,  2,  2,  1,  1,  2,  3,  2,  1,  2,  2,  2,  1,  1,
         0,  0,  1,  2,  1,  1,  1,  1,  2,  1,  1,  2,  2,  1,  1,  0,
        -1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  2,  1,  1,  0,  0,
        -1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,
        -2, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    Map map(data, Map::Dimensions({16, 16}));
    auto adjecent = map.getAdjecent(138);
    ASSERT_TRUE(equalVectorsUnordered(adjecent, std::vector<Target>({{121, 1}, {122, 2}, {123, 3}, {137, 1}, {139, 2}, {153, 2}, {154, 3}, {155, 3}})));
}

TEST(Map, getAdjecent_Test3)
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
    auto adjecent = map.getAdjecent(138);
    ASSERT_TRUE(equalVectorsUnordered(adjecent, std::vector<Target>({{121, 1}, {122, 2}, {123, 3}, {137, 1}, {139, 2}, {153, 2}, {154, 3}})));
}

TEST(MapParser, fParseDeparse_Test0)
{
    std::vector<int> data = {0,1,2,3};
    Map map(data, Map::Dimensions({2, 2}));

    std::stringstream file;
    Map::Parser parser;
    parser.deparse(map, file);

    auto resultmap = parser.parse(file);

    ASSERT_EQ(map.getDimensions().width, resultmap.getDimensions().width);
    ASSERT_EQ(map.getDimensions().height, resultmap.getDimensions().height);
    ASSERT_EQ(map.getData(), resultmap.getData());
}

TEST(MapParser, fParseDeparse_Test1)
{
    std::vector<int> data = {-5,1,2,3};
    Map map(data, Map::Dimensions({2, 2}));

    std::stringstream file;
    Map::Parser parser;
    parser.deparse(map, file);

    auto resultmap = parser.parse(file);

    ASSERT_EQ(map.getDimensions().width, resultmap.getDimensions().width);
    ASSERT_EQ(map.getDimensions().height, resultmap.getDimensions().height);
    ASSERT_EQ(map.getData(), resultmap.getData());
}