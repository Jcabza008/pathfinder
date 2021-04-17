#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>
#include <vector>

#include "random.h"
#include "graph.h"
#include "map.h"
#include "util.h"
#include "map_manip.h"

using namespace pathfinder;

class MockRandomIntGenerator : public RandomIntGenerator
{
    public:
    MOCK_METHOD0(getRandom, int(void));
}

TEST(MapManipulator, setHeight_Test0)
{
    MockRandomIntGenerator mockRandom;
    EXPECT_CALL(mockRandom, getRandom())
        .WillRepeatedly(Return(1));

    Map map(Map::Dimensions({10, 10}));
    MapManipulator mapManip(mockRandom);

    mapManip.setHeight(map, Map::Coordinates({0, 0}, 5));

    std::vector<int> expected = {
        5, 4, 3, 2, 1, 0, 0, 0, 0, 0,
        4, 4, 3, 2, 1, 0, 0, 0, 0, 0,
        3, 3, 3, 2, 1, 0, 0, 0, 0, 0,
        2, 2, 2, 2, 1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    ASSERT_EQ(map.getData(), expected);
}

TEST(MapManipulator, setHeight_Test1)
{
    MockRandomIntGenerator mockRandom;
    EXPECT_CALL(mockRandom, getRandom())
        .WillRepeatedly(Return(2));

    Map map(Map::Dimensions({10, 10}));
    MapManipulator mapManip(mockRandom);

    mapManip.setHeight(map, Map::Coordinates({0, 0}, 5));

    std::vector<int> expected = {
        5, 3, 1, 0, 0, 0, 0, 0, 0, 0,
        3, 3, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    ASSERT_EQ(map.getData(), expected);
}

TEST(MapManipulator, setHeight_Test2)
{
    MockRandomIntGenerator mockRandom;
    EXPECT_CALL(mockRandom, getRandom())
        .WillRepeatedly(Return(2));

    Map map(Map::Dimensions({10, 10}));
    MapManipulator mapManip(mockRandom);

    mapManip.setHeight(map, Map::Coordinates({5, 5}, 10));

    std::vector<int> expected = {
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  2,  2,  2,  2,  2,  2,  2,  2,  2,
         0,  2,  4,  4,  4,  4,  4,  4,  4,  2,
         0,  2,  4,  6,  6,  6,  6,  6,  4,  2,
         0,  2,  4,  6,  8,  8,  8,  6,  4,  2,
         0,  2,  4,  6,  8, 10,  8,  6,  4,  2,
         0,  2,  4,  6,  8,  8,  8,  6,  4,  2,
         0,  2,  4,  6,  6,  6,  6,  6,  4,  2,
         0,  2,  4,  4,  4,  4,  4,  4,  4,  2,
         0,  2,  2,  2,  2,  2,  2,  2,  2,  2
    };

    ASSERT_EQ(map.getData(), expected);
}

TEST(MapManipulator, affectHeight_Test0)
{
    MockRandomIntGenerator mockRandom;
    EXPECT_CALL(mockRandom, getRandom())
        .WillRepeatedly(Return(2));

    std::vector<int> original = {
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  2,  2,  2,  2,  2,  2,  2,  2,  2,
         0,  2,  4,  4,  4,  4,  4,  4,  4,  2,
         0,  2,  4,  6,  6,  6,  6,  6,  4,  2,
         0,  2,  4,  6,  8,  8,  8,  6,  4,  2,
         0,  2,  4,  6,  8, 10,  8,  6,  4,  2,
         0,  2,  4,  6,  8,  8,  8,  6,  4,  2,
         0,  2,  4,  6,  6,  6,  6,  6,  4,  2,
         0,  2,  4,  4,  4,  4,  4,  4,  4,  2,
         0,  2,  2,  2,  2,  2,  2,  2,  2,  2
    };

    Map map(original, Map::Dimensions({10, 10}));
    MapManipulator mapManip(mockRandom);

    mapManip.affectHeight(map, Map::Coordinates({3, 3}, 3));

    std::vector<int> expected = {
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  2,  2,  2,  2,  2,  2,  2,  2,  2,
         0,  2,  5,  5,  5,  4,  4,  4,  4,  2,
         0,  2,  5,  9,  7,  6,  6,  6,  4,  2,
         0,  2,  5,  7,  9,  8,  8,  6,  4,  2,
         0,  2,  4,  6,  8, 10,  8,  6,  4,  2,
         0,  2,  4,  6,  8,  8,  8,  6,  4,  2,
         0,  2,  4,  6,  6,  6,  6,  6,  4,  2,
         0,  2,  4,  4,  4,  4,  4,  4,  4,  2,
         0,  2,  2,  2,  2,  2,  2,  2,  2,  2
    };

    ASSERT_EQ(map.getData(), expected);
}