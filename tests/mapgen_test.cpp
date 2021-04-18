#include <gtest/gtest.h>
#include <fstream>
#include <algorithm>
#include <vector>

#include "graph.h"
#include "map.h"
#include "util.h"

using namespace pathfinder;

TEST(MapGenerat__Test, outputFile){
    DirectedGraphLinkedListImpl graph;
    auto vertices = graph.getVertices();
    for(int i : vertices){

    }
}

TEST(MapGenerat__Test, parseInput){
    std::string filename = "testFile.txt";
    std::ifstream file(filename, std::ios::in);
    file.open(filename);
    Parser prsr;
    if(file.is_open()){
        Map mp = prsr.parse(file);
        std::cout << "Map parsed successfully" << std::endl;
    }
    else 
        std::cout << "Cannot parse input file" << std::endl;
}
