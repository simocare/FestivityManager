#include "prodotto.h"

prodotto::prodotto(const std::string& nome, double quantita, double rimanenza, float prezzo) :
nome(nome), quantita(quantita), rimanenza(rimanenza), prezzoPorzione(prezzo) {}      //all'inizializzazione di un prodotto, la rimanenza ha lo stesso valore della quantità

prodotto::prodotto(const prodotto& p) : nome(p.nome), allergeni(p.allergeni), quantita(p.quantita), rimanenza(p.rimanenza), prezzoPorzione(p.prezzoPorzione) {}    

std::string prodotto::getNome() const { return nome; }

void prodotto::setNome(const std::string& nuovoNome) { nome=nuovoNome; }

void prodotto::aggiungiAllergene(const std::string& allergene) {
    allergeni.insert(allergene);
}

void prodotto::rimuoviAllergene(const std::string& allergene) {
    allergeni.erase(allergene);
}

bool prodotto::contieneAllergene(const std::string& allergene) const {
    return allergeni.count(allergene) > 0;
}

const std::set<std::string>& prodotto::getAllergeni() const {
    return allergeni;
}

double prodotto::getQuantita() const { return quantita; }
void prodotto::setQuantita(double newQ) { quantita=newQ; }

double prodotto::getRimanenza() const { return rimanenza; }
void prodotto::setRimanenza(double newR) { rimanenza=newR; }
void prodotto::aumentaRimanenza(double d) { rimanenza+=d; }
void prodotto::diminuisciRimanenza(double d) { aumentaRimanenza(-d); }

float prodotto::getPrezzoPorzione() const { return prezzoPorzione; }
void prodotto::setPrezzoPorzione(float prezzo) { prezzoPorzione = prezzo; }

void prodotto::serialize(Json::Value& prodJson) const {
    //controlla che il prodotto non sia già presente nel file
    if (exists(nome, prodJson["tipo"].asString(), pathManager::getPath("prodotti"))) {
        std::cerr << "Il prodotto " << nome << " è già presente nel file" << std::endl;
        return;
    }
    
    prodJson["nome"] = nome;
    prodJson["quantita"] = quantita;
    prodJson["rimanenza"] = rimanenza;
    prodJson["prezzoPorzione"] = prezzoPorzione;

    int i=0;
    for (const auto& allergene : allergeni) {
        prodJson["allergeni"][i] = allergene;
        ++i;
    }
}

void prodotto::save() const {
    //Carichiamo il file json esistente
    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();

    serialize(root);

    jfm.writeJsonFile(root);
}

int prodotto::exists(const std::string& nome, const std::string& tipo, const std::string& fileName) {
    JsonFileManager jfm(fileName);
    Json::Value root = jfm.readJsonFile();

    for (const auto& prod : root["prodotti"]) {
        if ((prod["nome"].asString() == nome) && (prod["tipo"].asString() == tipo)) {
            return 1;
        }
    }
    return 0;
}

void prodotto::remove(const std::string& nome, const std::string& tipo) {
    JsonFileManager jfm(pathManager::getPath("prodotti"));
    Json::Value root = jfm.readJsonFile();
    Json::Value& prodottiArray = root["prodotti"];

    Json::Value newProdottiArray(Json::arrayValue); // Creiamo un nuovo array

    for (unsigned int i = 0; i < prodottiArray.size(); ++i) {
        const Json::Value& prod = prodottiArray[i];
        if (prod["nome"].asString() != nome || prod["tipo"].asString() != tipo) {
            newProdottiArray.append(prod); // Conserviamo tutti gli elementi tranne quello da eliminare
        }
    }

    root["prodotti"] = newProdottiArray; // Sovrascriviamo l'array originale

    jfm.writeJsonFile(root);
}