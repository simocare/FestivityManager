#include "jsonFileManager.h"

JsonFileManager::JsonFileManager(std::string name) : fileName(name) {}

Json::Value JsonFileManager::readJsonFile() {
    //apriamo il file in lettura
    std::ifstream file(fileName);
    if(!file.is_open()) {
        std::cerr << "jfm: Errore nell'apertura del file " + fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    //parsing del file
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errors;
    if(!Json::parseFromStream(builder, file, &root, &errors)) {
        std::cerr << "jfm: Errore nel parsing del file " + fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    file.close();

    return root;    //ritorniamo il Json::Value
}

void JsonFileManager::writeJsonFile(Json::Value root) {
    //apriamo il file in scrittura
    std::ofstream file(fileName);
    if(!file.is_open()) {
        std::cerr << "jfm: Errore nell'apertura del file " + fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    
    //scrittura del file
    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &file);

    if(!file.good()) {
        std::cerr << "jfm: Errore nella scrittura del file " + fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    file.close();
}