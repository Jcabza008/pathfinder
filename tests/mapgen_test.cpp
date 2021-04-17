#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "graph.h"
#include "util.h"

using namespace PATHFINDER;

TEST(MapGenerat__Test, outputFile){
    DirectedGraphLinkedListImpl graph;
    auto vertices = graph.getVertices();
    for(int i : vertices){
        //out png
    }
    ASSERT_TRUE(/*file was created*/);
}