#include "pathManager.h"

const std::string pathManager::pathsjsonFileName = "/home/simone/UNI/2anno/PAO/Gestionale_sagra/paths.json";

std::string pathManager::getPath(const std::string& fileName) {
    Json::Value root;
    Json::Reader reader;
    std::ifstream file(pathsjsonFileName);
    if (!file.is_open()) {
        std::cerr << "pathManager: Impossibile aprire il file. " << strerror(errno) << pathsjsonFileName << std::endl;
        return "";
    }
    if (!reader.parse(file, root)) {
        std::cerr << "pathManager: Impossibile leggere il file " << pathsjsonFileName << std::endl;
        return "";
    }
    file.close();
    if (!root.isMember(fileName)) {
        std::cerr << "pathManager: Il file " << fileName << " non è presente nel file " << pathsjsonFileName << std::endl;
        return "";
    }
    return root[fileName].asString();
}
