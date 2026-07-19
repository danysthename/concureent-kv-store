#include <cstdlib>
#include"../src/storage_engine.h"   
#include<cassert>

storage_engine se;
int main() {
    se.PUT("1", "1");
    se.PUT("2", "2");
    se.PUT("3", "3");
    std::abort();
}