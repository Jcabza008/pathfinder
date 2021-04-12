#include <map.h>

pathfinder::Map::Map(){
    dimensions.size = 25;
    arr = new int[dimensions.size];
    /*== intialize arr to be flat, all heights = 0 ==*/
    for(int i = 0; i < dimensions.size; i++){
        arr[i] = 0;
    }
};

pathfinder::Map::Map(unsigned int x, unsigned int y){
    dimensions.xMax = x;
    dimensions.yMax = y;
    dimensions.size = x * y;    //
    arr = new int[dimensions.size];
    for(int i = 0; i < dimensions.size; i++){
        arr[i] = 0;
    }
};