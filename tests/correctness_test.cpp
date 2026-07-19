#include<iostream>
#include"../src/storage_engine.h"   
#include<cassert>




int main() {
    storage_engine se;
    se.PUT("1", "1");
    se.PUT("2", "2");
    assert(se.GET("1") == "1");
    assert(se.GET("2") == "2");
    se.DELETE("1");
    assert(se.GET("1") == std::nullopt);
    std::cout << "All test cases passed" << std::endl;
    return 0;
}