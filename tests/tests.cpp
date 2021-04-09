#include <gtest/gtest.h>
#include <list>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "graph.h"
#include "util.h"

#include "undirectedGraphLinkedListImpl_test.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}