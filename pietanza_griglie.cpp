#include "pietanza_griglie.h"

pietanza_griglie::pietanza_griglie(const std::string& nome, double quantita, double rimanenza, float prezzo, float peso) : prodotto(nome, quantita, rimanenza, prezzo), pesoPorzione(peso) {}
pietanza_griglie::pietanza_griglie(const pietanza_griglie& p) : prodotto(p), pesoPorzione(p.pesoPorzione) {}

pietanza_griglie* pietanza_griglie::clone() const { return new pietanza_griglie(*this); }

bool pietanza_griglie::operator==(const prodotto& p) const {
    if(typeid(p) != typeid(const pietanza_griglie&)) return false;
    if(getNome() != p.getNome()) return false;
    if(getQuantita() != p.getQuantita()) return false;
    if(getPrezzoPorzione() != p.getPrezzoPorzione()) return false;
    if(getAllergeni() != p.getAllergeni()) return false;
    if(getPeso() != dynamic_cast<const pietanza_griglie&>(p).getPeso()) return false;
    
    return true;
}

bool pietanza_griglie::operator!=(const prodotto& p) const {
    return !(*this == p);
}

float pietanza_griglie::getPeso() const { return pesoPorzione; }
void pietanza_griglie::setPeso(float peso) { pesoPorzione=peso; }

float pietanza_griglie::getPrezzoKg() { return getPrezzoPorzione() / pesoPorzione; }

void pietanza_griglie::serialize(Json::Value& root) const {
    Json::Value pietanzaGriglieJson;
    
    if(exists(getNome(), "pietanza_griglie", pathManager::getPath("prodotti"))){
        for (auto it = root["prodotti"].begin(); it != root["prodotti"].end(); ++it) {
            if ((*it)["nome"].asString() == getNome()) {
                pietanzaGriglieJson = *it;
                (*it)["quantita"] = getQuantita();
                (*it)["rimanenza"] = getRimanenza();
                (*it)["prezzoPorzione"] = getPrezzoPorzione();
                (*it)["allergeni"].clear();
                int i = 0;
                for (const auto& allergene : getAllergeni()) {
                    (*it)["allergeni"][i] = allergene;
                    i++;
                }
                (*it)["tipo"] = "pietanza_griglie";
                (*it)["peso"] = getPeso();
            }
        }
    } else {
        prodotto::serialize(pietanzaGriglieJson);
        pietanzaGriglieJson["tipo"] = "pietanza_griglie";
        pietanzaGriglieJson["peso"] = getPeso();
        root["prodotti"].append(pietanzaGriglieJson);
    }
}

pietanza_griglie* pietanza_griglie::deserialize(const Json::Value& root, const std::string& nome) {
    for (const Json::Value& pietanzaJson : root["prodotti"]) {
        if (pietanzaJson["nome"].asString() == nome && pietanzaJson["tipo"].asString() == "pietanza_griglie") {
            std::string nome = pietanzaJson["nome"].asString();
            double quantita = pietanzaJson["quantita"].asDouble();
            double rimanenza = pietanzaJson["rimanenza"].asDouble();
            float prezzo = pietanzaJson["prezzoPorzione"].asFloat();

            float peso = pietanzaJson["peso"].asFloat();

            pietanza_griglie* p = new pietanza_griglie(nome, quantita, rimanenza, prezzo, peso);
            for(const auto& allergene : pietanzaJson["allergeni"]) {
                p->aggiungiAllergene(allergene.asString());
            }

            return p;
        }
    }
    return nullptr;
}

void pietanza_griglie::stampaRimanenza() {
    double rim=getRimanenza(); double qu=getQuantita();
    std::cout << "Rimanenza/Quantità: " << rim << "/" << qu << " kg" << std::endl;
    std::cout << "Percentuale: " << rim/qu*100 << "%" << std::endl;
}

pietanza_griglie* pietanza_griglie::load(const std::string& nome) {
    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return nullptr;
    
    return deserialize(root, nome);
}

std::vector<pietanza_griglie*> pietanza_griglie::loadAll() {
    std::vector<pietanza_griglie*> pietanze;

    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return pietanze;

    for(const auto& pietanzaJson : root["prodotti"]) {
        if(pietanzaJson["tipo"].asString() == "pietanza_griglie") {
            std::string nome = pietanzaJson["nome"].asString();
            pietanze.push_back(deserialize(root, nome));
        }
    }
    return pietanze;
}