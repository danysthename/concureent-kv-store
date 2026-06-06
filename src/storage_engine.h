#pragma once
#include <string>
#include<optional>

class storage_engine {

public:
    void PUT(std::string key, std::string value);
    std::optional<std::string> GET(std::string key);
    void DELETE(std::string key);
};

