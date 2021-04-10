#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "graph.h"
#include "util.h"

using namespace PATHFINDER;

TEST(UndirectedGraphLinkedListImpl, addVertex_singleElement)
{
    DirectedGraphLinkedListImpl graph;
    // Assert there are no vertices
    auto vertices = graph.getVertices();
    ASSERT_TRUE(vertices.empty());

    // Add a vertex
    graph.addVertex(0);

    // Assert there is a single vertex 0
    vertices = graph.getVertices();
    ASSERT_EQ(vertices, std::vector<int>({0}));
}

TEST(UndirectedGraphLinkedListImpl, addEdge_verticesExists)
{
    DirectedGraphLinkedListImpl graph({1, 3}, {});
    // Assert vertices
    auto vertices = graph.getVertices();
    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(vertices, std::vector<int>({1, 3}));

    // Add a vertex
    graph.addEdge(1, 3, 5);

    // Assert there is a single vertex 0
    auto neighbors = graph.getAdjecent(1);
    std::sort(neighbors.begin(), neighbors.end());
    ASSERT_EQ(neighbors, std::vector<Target>({ {3, 5} }));
}