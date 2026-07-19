#pragma once
#include<string>
#include<fstream>
class storage_engine;   
class wal
{
private:
    std::ofstream file{"log.txt", std::ios::app}; // open in append mode
        
public:
    void log(std::string operation, std::string key, std::string value);
    
    void recover(storage_engine& obj);

};


