#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "graph.h"
#include "util.h"

using namespace pathfinder;

TEST(UndirectedGraphLinkedListImpl, addVertex_singleVertex)
{
    DirectedGraphLinkedListImpl graph;
    auto vertices = graph.getVertices();
    ASSERT_TRUE(vertices.empty());

    graph.addVertex(0);

    vertices = graph.getVertices();
    ASSERT_EQ(vertices, std::vector<int>({0}));
}

TEST(UndirectedGraphLinkedListImpl, addVertex_severalVertices)
{
    DirectedGraphLinkedListImpl graph;
    auto vertices = graph.getVertices();
    ASSERT_TRUE(vertices.empty());

    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(5);
    graph.addVertex(2);
    graph.addVertex(3);

    vertices = graph.getVertices();
    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(vertices, std::vector<int>({0, 1, 2, 3, 5}));
}

TEST(UndirectedGraphLinkedListImpl, addEdge_verticesCreatedPreviously)
{
    DirectedGraphLinkedListImpl graph({1, 3});
    auto vertices = graph.getVertices();
    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(vertices, std::vector<int>({1, 3}));

    graph.addEdge(1, 3, 5);

    auto neighbors = graph.getAdjecent(1);
    std::sort(neighbors.begin(), neighbors.end());
    ASSERT_EQ(neighbors, std::vector<Target>({ {3, 5} }));
}

TEST(UndirectedGraphLinkedListImpl, addEdge_creatingVerticesAsNeeded)
{
    DirectedGraphLinkedListImpl graph;
    auto vertices = graph.getVertices();
    ASSERT_TRUE(vertices.empty());

    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 6);
    graph.addEdge(2, 1, 1);

    vertices = graph.getVertices();
    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(vertices, std::vector<int>({1, 2, 3}));
}

TEST(UndirectedGraphLinkedListImpl, removeVertex_vertexExists)
{
    DirectedGraphLinkedListImpl graph({1, 3});
    auto vertices = graph.getVertices();
    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(vertices, std::vector<int>({1, 3}));

    graph.removeVertex(3);

    vertices = graph.getVertices();
    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(vertices, std::vector<int>({1}));
}

TEST(UndirectedGraphLinkedListImpl, removeVertex_vertexDoesNotExists)
{
    DirectedGraphLinkedListImpl graph;
    // Vertex does not exists nothing should happen
    ASSERT_NO_THROW(graph.removeVertex(3););
}

TEST(UndirectedGraphLinkedListImpl, removeEdge_edgeExists)
{
    DirectedGraphLinkedListImpl graph;
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 6);
    graph.addEdge(2, 1, 1);

    auto neighbors_2 = graph.getAdjecent(2);
    std::sort(neighbors_2.begin(), neighbors_2.end());
    ASSERT_EQ(neighbors_2, std::vector<Target>({{1, 1}, {3, 6}}));

    graph.removeEdge(2, 1);
    neighbors_2 = graph.getAdjecent(2);
    std::sort(neighbors_2.begin(), neighbors_2.end());
    ASSERT_EQ(neighbors_2, std::vector<Target>({{3, 6}}));
}