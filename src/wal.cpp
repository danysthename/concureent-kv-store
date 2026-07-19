#include "wal.h"
#include "storage_engine.h"
#include <sstream>
#include <iostream>

void wal::log(std::string operation, std::string key, std::string value) {
    file << operation << " " << key << " " << value << "\n";
    file.flush();
}

void wal::recover(storage_engine &obj) {

  std::ifstream file("log.txt");

  if (!file.is_open())
    return;

  std::string line;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string word;

    if (ss >> word) {
      if (word == "PUT") {
        std::string key, value;
        ss >> key >> value;
        obj.PUT(key, value);
      }
      if (word == "DELETE") {
        std::string key;
        ss >> key;
        obj.DELETE(key);
      }
    }
  }
}
