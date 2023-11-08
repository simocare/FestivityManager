#include "bevanda.h"

bevanda::bevanda(const std::string& nome, double quantita, double rimanenza, float prezzo, float volume, bool alcool, bool caffeina, bool zero) : prodotto(nome, quantita, rimanenza, prezzo), volume_unit(volume), alcool(alcool), caffeina(caffeina), zero(zero) {}
bevanda::bevanda(const bevanda& b) : prodotto(b), volume_unit(b.volume_unit), alcool(b.alcool), caffeina(b.caffeina), zero(b.zero) {}

bevanda* bevanda::clone() const { return new bevanda(*this); }

bool bevanda::operator==(const prodotto& p) const {
    //controlla che p sia una bevanda
    if (typeid(p) != typeid(const bevanda&)) return false;

    if (getNome() != p.getNome()) return false;
    if (getQuantita() != p.getQuantita()) return false;
    if (getRimanenza() != p.getRimanenza()) return false;
    if (getPrezzoPorzione() != p.getPrezzoPorzione()) return false;
    if (getAllergeni() != p.getAllergeni()) return false;
    if (typeid(p) != typeid(const bevanda&)) return false;
    if (getVolumeUnit() != dynamic_cast<const bevanda&>(p).volume_unit) return false;
    if (haAlcool() != dynamic_cast<const bevanda&>(p).alcool) return false;
    if (haCaffeina() != dynamic_cast<const bevanda&>(p).caffeina) return false;
    if (isZero() != dynamic_cast<const bevanda&>(p).zero) return false;
    return true;
}

bool bevanda::operator!=(const prodotto& p) const {
    return !(*this == p);
}

float bevanda::getVolumeUnit() const { return volume_unit; }

float bevanda::getPrezzoLitro() const { return getPrezzoPorzione()/volume_unit; }

bool bevanda::haAlcool() const { return alcool; }
bool bevanda::haCaffeina() const { return caffeina; }
bool bevanda::isZero() const { return zero; }

void bevanda::setVolumeUnit(float volume) { volume_unit = volume; }
void bevanda::setAlcool(bool valore) { alcool = valore; }
void bevanda::setCaffeina(bool valore) { caffeina = valore; }
void bevanda::setZero(bool valore) { zero = valore; }

void bevanda::stampaRimanenza() {
    double rim=getRimanenza(); double qu=getQuantita();
    std::cout << "Rimanenza/Quantità: " << rim << "/" << qu << " litri" << std::endl;
    std::cout << "Percentuale: " << rim/qu*100 << "%" << std::endl;
}

void bevanda::serialize(Json::Value& root) const {
    // Dichiarazione di bevandaJson
    Json::Value bevandaJson;

    // Verifica se l'oggetto bevanda esiste già
    if (exists(getNome(), "bevanda", pathManager::getPath("prodotti"))) {
        // Sovrascrivi i dati esistenti con i nuovi dati
        for (auto it = root["prodotti"].begin(); it != root["prodotti"].end(); ++it) {
            if ((*it)["nome"].asString() == getNome()) {
                bevandaJson = *it; // Aggiorna l'oggetto bevandaJson con i dati esistenti
                (*it)["quantita"] = getQuantita();
                (*it)["rimanenza"] = getRimanenza();
                (*it)["prezzoPorzione"] = getPrezzoPorzione();
                (*it)["allergeni"].clear();
                int i = 0;
                for (const auto& allergene : getAllergeni()) {
                    (*it)["allergeni"][i] = allergene;
                    ++i;
                }
                (*it)["tipo"] = "bevanda";
                (*it)["volume_unit"] = volume_unit;
                (*it)["alcool"] = alcool;
                (*it)["caffeina"] = caffeina;
                (*it)["zero"] = zero;
            }
        }
    } else {
        // Se l'oggetto non esiste, aggiungilo al JSON
        prodotto::serialize(bevandaJson);
        bevandaJson["tipo"] = "bevanda";
        bevandaJson["volume_unit"] = volume_unit;
        bevandaJson["alcool"] = alcool;
        bevandaJson["caffeina"] = caffeina;
        bevandaJson["zero"] = zero;
        root["prodotti"].append(bevandaJson);
    }
}

bevanda* bevanda::deserialize(const Json::Value& root, const std::string& nome) {
    for (const Json::Value& bevandaJson : root["prodotti"]) {
        if (bevandaJson["nome"].asString() == nome && bevandaJson["tipo"].asString() == "bevanda") {
            std::string nome = bevandaJson["nome"].asString();
            double quantita = bevandaJson["quantita"].asDouble();
            double rimanenza = bevandaJson["rimanenza"].asDouble();
            float prezzo = bevandaJson["prezzoPorzione"].asFloat();

            float volume_unit = bevandaJson["volume_unit"].asFloat();
            bool alcool = bevandaJson["alcool"].asBool();
            bool caffeina = bevandaJson["caffeina"].asBool();
            bool zero = bevandaJson["zero"].asBool();

            bevanda* b = new bevanda(nome, quantita, rimanenza, prezzo, volume_unit, alcool, caffeina, zero);
            for(const auto& allergene : bevandaJson["allergeni"]) {
                b->aggiungiAllergene(allergene.asString());
            }

            return b;
        }
    }
    return nullptr;
}

bevanda* bevanda::load(const std::string& nome) {
    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return nullptr;
    
    return deserialize(root, nome);
}

std::vector<bevanda*> bevanda::loadAll() {
    std::vector<bevanda*> bevande;

    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return bevande;

    for (const Json::Value& bevandaJson : root["prodotti"]) {
        if (bevandaJson["tipo"].asString() == "bevanda") {
            std::string nome = bevandaJson["nome"].asString();
            bevanda* b = deserialize(root, nome);
            if(b) bevande.push_back(b);
        }
    }
    return bevande;
}