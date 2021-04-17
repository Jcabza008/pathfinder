#include <algorithm>
#include <bits/stdc++.h>
#include <functional>
#include <list>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "graph.h"
#include "map.h"
#include "map_manip.h"
#include "util.h"
#include "random.h"
#include "algorithms.h"

#include "graph_test.cpp"
#include "map_test.cpp"
#include "map_manip_test.cpp"
#include "priority_queue_test.cpp"
#include "dijkstrasAlgorithm_test.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}