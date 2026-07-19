#include<iostream>
#include"../src/storage_engine.h"   
#include<cassert>


int main() {
    storage_engine se;
    assert(se.GET("1") == "1");
    assert(se.GET("2") == "2");
    assert(se.GET("3") == "3");
    std::cout << "All test cases passed" << std::endl;
    return 0;
}