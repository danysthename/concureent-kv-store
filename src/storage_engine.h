#pragma once
#include <string>
#include <optional>
#include <unordered_map>
#include<shared_mutex>

class storage_engine {
private:
    std::unordered_map<std::string, std::string> mp;
    std::shared_mutex mx;

public:
    void PUT(std::string key, std::string value);
    std::optional<std::string> GET(std::string key);
    void DELETE(std::string key);
};

