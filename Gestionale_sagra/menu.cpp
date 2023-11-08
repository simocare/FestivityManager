#include "menu.h"

menu::menu() : prodotti() {}

int menu::aggiungiProdotto(const std::string& nome, const std::string& tipo) {
    
    //se è vuoto non controlliamo
    if(prodotti.isEmpty()) {
        prodotti.insert(nome, tipo);
        return 0;
    }

    //controlliamo che esista nel file prodotti.json
    if (!prodotto::exists(nome, tipo, pathManager::getPath("prodotti"))) {
        std::cerr << "menu: " << tipo << " " << nome << " non presente nel file prodotti.json" << std::endl;
        return 1;
    }
    
    //controlliamo che non sia già presente nel menu
    for (auto it = prodotti.begin(); !it.isPastTheEnd(); ++it) {
        if (it.firstInfo() == nome && it.secondInfo() == tipo) {
            std::cerr << "menu: " << tipo << " " << nome << " già presente nel menu" << std::endl;
            return 2;
        }
    }
    prodotti.insert(nome, tipo);
    return 0;
}

void menu::rimuoviProdotto(const std::string& nome) {
    for (auto it = prodotti.begin(); !it.isPastTheEnd(); ++it) {
        if (it.firstInfo() == nome) {
            prodotti.remove(nome);
            return;
        }
    }
    std::cerr << "menu: prodotto non presente nel menu" << std::endl;
}

const std::vector<std::string*> menu::getTipi() const {
    std::vector<std::string*> tipi;
    for (auto it = prodotti.begin(); !it.isPastTheEnd(); ++it) {
        bool found = false; //variabile che dice se il tipo è già presente nel vettore tipi
        for (auto j = tipi.begin(); j != tipi.end() && !found; ++j) {
            if (**j == it.secondInfo()) {
                found = true;
            }
        }
        if (!found) {
            tipi.push_back(new std::string(it.secondInfo()));
        }
    }
    return tipi;
}

const std::vector<std::string*> menu::getProdotti(const std::string& tipo) const {
    std::vector<std::string*> prodottiTipo;
    for (auto it = prodotti.begin(); !it.isPastTheEnd(); ++it) {
        if (it.secondInfo() == tipo) {
            prodottiTipo.push_back(new std::string(it.firstInfo()));
        }
    }
    return prodottiTipo;
}

void menu::serialize(Json::Value& menuJson) const {
    
    for (auto it = prodotti.begin(); !it.isPastTheEnd(); ++it) {
        menuJson[it.secondInfo()].append(it.firstInfo());
    }
}

menu* menu::deserialize(const Json::Value& root) {
    menu* m = new menu();
    
    for (const auto& tipo : root.getMemberNames()) {        //scorro i tipi
        for (const auto& prodotto : root[tipo]) {           //scorro i prodotti di quel tipo
            m->aggiungiProdotto(prodotto.asString(), tipo);
        }
    }
    return m;
}

void menu::save() const {
    Json::Value menuJson;
    serialize(menuJson);
    
    JsonFileManager jfm(pathManager::getPath("menu"));
    jfm.writeJsonFile(menuJson);
}

menu* menu::load() {
    JsonFileManager jfm(pathManager::getPath("menu"));
    Json::Value root = jfm.readJsonFile();
    if (root.isNull())
        return nullptr;
    
    return deserialize(root);
}
