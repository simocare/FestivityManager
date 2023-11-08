#include "pietanza_cucina.h"

pietanza_cucina::pietanza_cucina(const std::string& nome, double quantita, double rimanenza, float prezzo) : prodotto(nome, quantita, rimanenza, prezzo) {}
pietanza_cucina::pietanza_cucina(const pietanza_cucina& p) : prodotto(p) {}

pietanza_cucina* pietanza_cucina::clone() const { return new pietanza_cucina(*this); }

bool pietanza_cucina::operator==(const prodotto& p) const {
    if(typeid(p) != typeid(const pietanza_cucina&)) return false;
    if(getNome() != p.getNome()) return false;
    if(getQuantita() != p.getQuantita()) return false;
    if(getPrezzoPorzione() != p.getPrezzoPorzione()) return false;
    if(getAllergeni() != p.getAllergeni()) return false;
    return true;
}

bool pietanza_cucina::operator!=(const prodotto& p) const {
    return !(*this == p);
}

void pietanza_cucina::serialize(Json::Value& root) const {
    Json::Value pietanzaCucinaJson;
    
    if(exists(getNome(), "pietanza_cucina", pathManager::getPath("prodotti"))){
        for (auto it = root["prodotti"].begin(); it != root["prodotti"].end(); ++it) {
            if ((*it)["nome"].asString() == getNome()) {
                pietanzaCucinaJson = *it;
                (*it)["quantita"] = getQuantita();
                (*it)["rimanenza"] = getRimanenza();
                (*it)["prezzoPorzione"] = getPrezzoPorzione();
                (*it)["allergeni"].clear();
                int i = 0;
                for (const auto& allergene : getAllergeni()) {
                    (*it)["allergeni"][i] = allergene;
                    i++;
                }
                (*it)["tipo"] = "pietanza_cucina";
            }
        }
    } else {
        prodotto::serialize(pietanzaCucinaJson);
        pietanzaCucinaJson["tipo"] = "pietanza_cucina";
        root["prodotti"].append(pietanzaCucinaJson);
    }
}

pietanza_cucina* pietanza_cucina::deserialize(const Json::Value& root, const std::string& nome) {
    for(const auto& pietanzaCucinaJson : root["prodotti"]) {
        if(pietanzaCucinaJson["nome"].asString() == nome && pietanzaCucinaJson["tipo"].asString() == "pietanza_cucina") {
            std::string nome = pietanzaCucinaJson["nome"].asString();
            double quantita = pietanzaCucinaJson["quantita"].asDouble();
            double rimanenza = pietanzaCucinaJson["rimanenza"].asDouble();
            float prezzo = pietanzaCucinaJson["prezzoPorzione"].asFloat();

            pietanza_cucina* p = new pietanza_cucina(nome, quantita, rimanenza, prezzo);
            for(const auto& allergene : pietanzaCucinaJson["allergeni"]) {
                p->aggiungiAllergene(allergene.asString());
            }

            return p;
        }
    }
    return nullptr;
}

void pietanza_cucina::stampaRimanenza() {
    double rim=getRimanenza(); double qu=getQuantita();

    std::cout << "Rimanenza/Quantità: " << rim << "/" << qu << " porzioni" << std::endl;
    std::cout << "Percentuale: " << rim/qu*100 << "%" << std::endl;
}

pietanza_cucina* pietanza_cucina::load(const std::string& nome) {
    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return nullptr;
    
    return deserialize(root, nome);
}

std::vector<pietanza_cucina*> pietanza_cucina::loadAll() {
    std::vector<pietanza_cucina*> pietanze;

    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return pietanze;

    for(const auto& pietanzaCucinaJson : root["prodotti"]) {
        if(pietanzaCucinaJson["tipo"].asString() == "pietanza_cucina") {
            std::string nome = pietanzaCucinaJson["nome"].asString();
            pietanza_cucina* p = deserialize(root, nome);
            if(p) pietanze.push_back(p);
        }
    }
    return pietanze;
}