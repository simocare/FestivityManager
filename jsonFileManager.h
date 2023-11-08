#ifndef JSONFILEMANAGER_H
#define JSONFILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

class JsonFileManager {
private:
    std::string fileName;   //nome del file
public:
    JsonFileManager(std::string);
    Json::Value readJsonFile();
    void writeJsonFile(Json::Value);
};

#endif