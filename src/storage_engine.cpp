#include"storage_engine.h"
#include<mutex>


void storage_engine::PUT(std::string key, std::string value) {
    std::unique_lock<std::shared_mutex> lock(mx);
    mp[key] = value;
}

std::optional<std::string> storage_engine::GET(std::string key) {
    std::shared_lock<std::shared_mutex> lock(mx);
    if(mp.count(key))
        return mp[key];
    return {};
}

void storage_engine::DELETE(std::string key) {
    std::unique_lock<std::shared_mutex> lock(mx);
    mp.erase(key);
}