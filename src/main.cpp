#include "storage_engine.h"
#include <iostream>
#include <string>

int main() {
    storage_engine se;
    while(true) {
        std::string operation;
        std::cin >> operation;
        if(operation == "PUT") {
            std::string key, value;
            std::cin >> key >> value;
            se.PUT(key, value);
        }
        if(operation == "GET") {
            std::string key;
            std::cin >> key;
            std::optional<std::string> value = se.GET(key);
            if(value) {
                std::cout << *value << std::endl;
            }
        }
        if(operation == "DELETE") {
            std::string key;
            std::cin >> key;
            se.DELETE(key);
        }
        if(operation == "QUIT")
            break;
    }

    return 0;
}