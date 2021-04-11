#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bits/stdc++.h>
#include <functional>
#include <list>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "pf_algoritm.h"
#include "priority_queue.h"

using namespace PATHFINDER;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::_;

class MockDirectedGraph : public DirectedGraph
{
    public:
    MOCK_METHOD0(getVertices, std::vector<int>());
    MOCK_METHOD1(getAdjecent, std::vector<Target>(int id));

    // Not Used
    MOCK_METHOD1(addVertex, void(int));
    MOCK_METHOD3(addEdge, void(int, int, int));
    MOCK_METHOD1(removeVertex, void(int));
    MOCK_METHOD2(removeEdge, void(int, int));
};

TEST(DijkstrasAlgorithm, findPaths_severalVertices)
{
    MockDirectedGraph graph;
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

    ASSERT_EQ(paths[0].cost, 0);
    ASSERT_EQ(paths[1].cost, 4);
    ASSERT_EQ(paths[2].cost, 5);
    ASSERT_EQ(paths[3].cost, 13);
    ASSERT_EQ(paths[4].cost, 22);
    ASSERT_EQ(paths[5].cost, 13);
    ASSERT_EQ(paths[6].cost, 6);
}