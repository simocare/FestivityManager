#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <string>
#include <json/json.h>
#include <fstream>
#include <iostream>

class pathManager {
public:
    static std::string getPath(const std::string&); // Restituisce il path del file passato come parametro

    static const std::string pathsjsonFileName;

private:
    pathManager() = default; // Costruttore privato per impedire istanze della classe
};

#endif
