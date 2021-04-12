#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bits/stdc++.h>
#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "algorithms.h"
#include "priority_queue.h"

using namespace pathfinder;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::_;

class MockGraph : public Graph
{
    public:
    MOCK_METHOD0(getVertices, std::vector<int>());
    MOCK_METHOD1(getAdjecent, std::vector<Target>(int id));
};

TEST(DijkstrasAlgorithm, findPaths_singleVertices)
{
    MockGraph graph;
    std::vector<int> vertices = {0};
    std::unordered_map<int, std::vector<Target>> adjTable;
    adjTable.insert({0, { }});

    EXPECT_CALL(graph, getVertices())
        .WillRepeatedly(Return(vertices));
    EXPECT_CALL(graph, getAdjecent(_))
        .WillRepeatedly(Invoke([&](int id){ return adjTable[id]; }));

    DijkstrasAlgorithm dijkstras;
    auto paths = dijkstras.findPaths(&graph, 0);

    ASSERT_EQ(paths[0], PathData({0, -1}));
}

TEST(DijkstrasAlgorithm, findPaths_noVertices)
{
    MockGraph graph;
    std::vector<int> vertices = {};
    std::unordered_map<int, std::vector<Target>> adjTable;

    EXPECT_CALL(graph, getVertices())
        .WillRepeatedly(Return(vertices));
    EXPECT_CALL(graph, getAdjecent(_))
        .WillRepeatedly(Invoke([&](int id){ return adjTable[id]; }));

    DijkstrasAlgorithm dijkstras;
    auto paths = dijkstras.findPaths(&graph, 0);

    ASSERT_TRUE(paths.empty());
}

TEST(DijkstrasAlgorithm, findPaths_severalVerticesDirected0)
{
    MockGraph graph;
    std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6};
    std::unordered_map<int, std::vector<Target>> adjTable;
    adjTable.insert({0, { Target{1, 4}, Target{6, 10} }});
    adjTable.insert({1, { Target{2, 1}, Target{6,  2} }});
    adjTable.insert({2, { Target{3, 8} }});
    adjTable.insert({3, { Target{4, 9}, Target{5,  5} }});
    adjTable.insert({4, { }});
    adjTable.insert({5, { Target{4, 12} }});
    adjTable.insert({6, { Target{5,  7}, Target{2, 6} }});

    EXPECT_CALL(graph, getVertices())
        .WillRepeatedly(Return(vertices));
    EXPECT_CALL(graph, getAdjecent(_))
        .WillRepeatedly(Invoke([&](int id){ return adjTable[id]; }));

    DijkstrasAlgorithm dijkstras;
    auto paths = dijkstras.findPaths(&graph, 0);

    ASSERT_EQ(paths[0], PathData({ 0, -1}));
    ASSERT_EQ(paths[1], PathData({ 4,  0}));
    ASSERT_EQ(paths[2], PathData({ 5,  1}));
    ASSERT_EQ(paths[3], PathData({13,  2}));
    ASSERT_EQ(paths[4], PathData({22,  3}));
    ASSERT_EQ(paths[5], PathData({13,  6}));
    ASSERT_EQ(paths[6], PathData({ 6,  1}));
}

TEST(DijkstrasAlgorithm, findPaths_severalVerticesDirected1)
{
    MockGraph graph;
    std::vector<int> vertices = {0, 1, 3, 4, 5, 6, 8, 10};
    std::unordered_map<int, std::vector<Target>> adjTable;
    adjTable.insert({ 0, { Target{1,  2}, Target{5, 10} }});
    adjTable.insert({ 1, { Target{4,  1}, Target{3,  5} }});
    adjTable.insert({ 3, { Target{4,  2}, Target{6,  7}, Target{10, 25} }});
    adjTable.insert({ 4, { }});
    adjTable.insert({ 5, { Target{6,  3} }});
    adjTable.insert({ 6, { }});
    adjTable.insert({ 8, { Target{6,  6} }});
    adjTable.insert({10, { Target{8,  2} }});

    EXPECT_CALL(graph, getVertices())
        .WillRepeatedly(Return(vertices));
    EXPECT_CALL(graph, getAdjecent(_))
        .WillRepeatedly(Invoke([&](int id){ return adjTable[id]; }));

    DijkstrasAlgorithm dijkstras;
    auto paths = dijkstras.findPaths(&graph, 0);

    ASSERT_EQ(paths[0],  PathData({ 0, -1}));
    ASSERT_EQ(paths[1],  PathData({ 2,  0}));
    ASSERT_EQ(paths[3],  PathData({ 7,  1}));
    ASSERT_EQ(paths[4],  PathData({ 3,  1}));
    ASSERT_EQ(paths[5],  PathData({10,  0}));
    ASSERT_EQ(paths[6],  PathData({13,  5}));
    ASSERT_EQ(paths[8],  PathData({34, 10}));
    ASSERT_EQ(paths[10], PathData({32,  3}));
}

TEST(DijkstrasAlgorithm, findPaths_severalVerticesUndirected0)
{
    MockGraph graph;
    std::vector<int> vertices = {0, 1, 2, 3, 4, 5};
    std::unordered_map<int, std::vector<Target>> adjTable;
    adjTable.insert({ 0, { Target{1,  1}, Target{2,  5} }});
    adjTable.insert({ 1, { Target{0,  1}, Target{2,  2}, Target{3,  3} }});
    adjTable.insert({ 2, { Target{0,  5}, Target{1,  2}, Target{4,  6}, Target{5, 10} }});
    adjTable.insert({ 3, { Target{1,  3}, Target{4,  2}, Target{5,  5} }});
    adjTable.insert({ 4, { Target{2,  6}, Target{3,  2} }});
    adjTable.insert({ 5, { Target{2, 10}, Target{3,  5} }});

    EXPECT_CALL(graph, getVertices())
        .WillRepeatedly(Return(vertices));
    EXPECT_CALL(graph, getAdjecent(_))
        .WillRepeatedly(Invoke([&](int id){ return adjTable[id]; }));

    DijkstrasAlgorithm dijkstras;
    auto paths = dijkstras.findPaths(&graph, 1);

    ASSERT_EQ(paths[0], PathData({1,  1}));
    ASSERT_EQ(paths[1], PathData({0, -1}));
    ASSERT_EQ(paths[2], PathData({2,  1}));
    ASSERT_EQ(paths[3], PathData({3,  1}));
    ASSERT_EQ(paths[4], PathData({5,  3}));
    ASSERT_EQ(paths[5], PathData({8,  3}));
}

TEST(DijkstrasAlgorithm, findPaths_severalVerticesUndirected1)
{
    MockGraph graph;
    std::vector<int> vertices = {0, 1, 3, 4, 5, 6, 8, 10};
    std::unordered_map<int, std::vector<Target>> adjTable;
    adjTable.insert({ 0, { Target{1,  2}, Target{5, 10} }});
    adjTable.insert({ 1, { Target{0,  2}, Target{4,  1}, Target{3, 5} }});
    adjTable.insert({ 3, { Target{1,  5}, Target{4,  2}, Target{6, 7}, Target{10, 25} }});
    adjTable.insert({ 4, { Target{1,  1}, Target{3,  2} }});
    adjTable.insert({ 5, { Target{0, 10}, Target{6,  3} }});
    adjTable.insert({ 6, { Target{5,  3}, Target{3,  7}, Target{8, 6} }});
    adjTable.insert({ 8, { Target{6,  6}, Target{10, 2} }});
    adjTable.insert({10, { Target{3, 25}, Target{8,  2} }});

    EXPECT_CALL(graph, getVertices())
        .WillRepeatedly(Return(vertices));
    EXPECT_CALL(graph, getAdjecent(_))
        .WillRepeatedly(Invoke([&](int id){ return adjTable[id]; }));

    DijkstrasAlgorithm dijkstras;
    auto paths = dijkstras.findPaths(&graph, 0);

    ASSERT_EQ(paths[0],  PathData({ 0,-1}));
    ASSERT_EQ(paths[1],  PathData({ 2, 0}));
    ASSERT_EQ(paths[3],  PathData({ 5, 4}));
    ASSERT_EQ(paths[4],  PathData({ 3, 1}));
    ASSERT_EQ(paths[5],  PathData({10, 0}));
    ASSERT_EQ(paths[6],  PathData({12, 3}));
    ASSERT_EQ(paths[8],  PathData({18, 6}));
    ASSERT_EQ(paths[10], PathData({20, 8}));
}