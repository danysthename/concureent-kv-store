#include<iostream>
#include"../src/storage_engine.h"   
#include<chrono>
#include<thread>

int main(){
    std::remove("log.txt");
    auto start_put = std::chrono::high_resolution_clock::now();
    storage_engine se;
    int const amount = 10000;
    for(int i = 0; i < amount; i++) {   
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        se.PUT(key, value);
    }    
    auto stop_put = std::chrono::high_resolution_clock::now();
    auto duration_put = std::chrono::duration_cast<std::chrono::microseconds>(stop_put - start_put);
    double ops_put_per_sec = (amount / (duration_put.count() / 1e6));
    std::cout << "PUT Throughput: " << ops_put_per_sec << " ops/sec" << std::endl;

    auto start_get = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < amount; i++) {
        std::string key = "key" + std::to_string(i);
        se.GET(key);
    }
    auto stop_get = std::chrono::high_resolution_clock::now();
    auto duration_get = std::chrono::duration_cast<std::chrono::microseconds>(stop_get - start_get);
    double ops_get_per_sec = (amount / (duration_get.count() / 1e6));
    std::cout << "GET Throughput: " << ops_get_per_sec << " ops/sec" << std::endl;

    auto start_multi = std::chrono::high_resolution_clock::now();
    std::thread writer_1([&](){
        for(int i = 0; i < amount / 4; i++){
            std::string key = "key" + std::to_string(i);
            std::string value = "value" + std::to_string(i);
            se.PUT(key, value);
        }
    });
    std::thread writer_2([&](){
        for(int i = amount / 4; i < amount / 2; i++){
            std::string key = "key" + std::to_string(i);
            std::string value = "value" + std::to_string(i);
            se.PUT(key, value);
        }
    });
    std::thread writer_3([&](){
        for(int i = amount / 2; i < (3 * amount) / 4; i++){
            std::string key = "key" + std::to_string(i);
            std::string value = "value" + std::to_string(i);
            se.PUT(key, value);
        }
    });
    std::thread writer_4([&](){
        for(int i = (3 * amount) / 4; i < amount; i++){
            std::string key = "key" + std::to_string(i);
            std::string value = "value" + std::to_string(i);
            se.PUT(key, value);
        }
    });

    std::thread reader_1([&](){
        for(int i = 0; i < amount / 4; i++){
            std::string key = "key" + std::to_string(i);
            se.GET(key);
        }
    });
    std::thread reader_2([&](){
        for(int i = amount / 4; i < amount / 2; i++){
            std::string key = "key" + std::to_string(i);
            se.GET(key);
        }
    });
    std::thread reader_3([&](){
        for(int i = amount / 2; i < (3 * amount) / 4; i++){
            std::string key = "key" + std::to_string(i);
            se.GET(key);
        }
    });
    std::thread reader_4([&](){
        for(int i = (3 * amount) / 4; i < amount; i++){
            std::string key = "key" + std::to_string(i);
            se.GET(key);
        }
    });

    writer_1.join();
    writer_2.join();
    writer_3.join();
    writer_4.join();
    reader_1.join();
    reader_2.join();
    reader_3.join();
    reader_4.join();
    
    auto stop_multi = std::chrono::high_resolution_clock::now();
    auto duration_multi = std::chrono::duration_cast<std::chrono::microseconds>(stop_multi - start_multi);
    double ops_multi_per_sec = (amount / (duration_multi.count() / 1e6));
    std::cout << "Multi-Thread Throughput: " << ops_multi_per_sec << " ops/sec" << std::endl;

    return 0;
}