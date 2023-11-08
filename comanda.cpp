#include "comanda.h"

comanda::comanda(int numero, user* cameriere, user* distributore, bool asporto) :
num(numero), asporto(asporto) {

    //controlliamo che i puntatori non siano null
    if (cameriere == nullptr) {
        throw std::invalid_argument("Il puntatore al cameriere non può essere nullo.");
    }
    else if (distributore == nullptr) {
        throw std::invalid_argument("Il puntatore al distributore non può essere nullo.");
    }
    //controlliamo che il cameriere sia un cameriere
    else if (cameriere->getRuolo() != "cameriere") {
        throw std::invalid_argument("Il puntatore al cameriere deve puntare ad uno user di tipo cameriere.");
    }
    //controlliamo che il distributore sia un distributore
    else if (distributore->getRuolo() != "distributore") {
        throw std::invalid_argument("Il puntatore al distributore deve puntare ad uno user di tipo distributore.");
    }
    else{
        this->cameriere = cameriere;
        this->distributore = distributore;
    }
}

comanda::comanda(const comanda& c) : num(c.num), cameriere(c.cameriere), distributore(c.distributore), asporto(c.asporto), ordine(c.ordine) {}

int comanda::getNumero() const { return num; }
void comanda::setNumero(int numero) { num=numero; }

user* comanda::getCameriere() const { return cameriere; }
void comanda::setCameriere(user* newCam) { cameriere=newCam; }

user* comanda::getDistributore() const { return distributore; }
void comanda::setDistributore(user* newDistr) { distributore=newDistr; }

bool comanda::isAsporto() const { return asporto; }
void comanda::setAsporto(bool a) { asporto=a; }

myContainer<prodotto*, int> comanda::getOrdine() const { return ordine; }

bool comanda::isMember(prodotto* prod) const {
    if(ordine.isEmpty()){
        std::cerr << "Non ci sono prodotti." << std::endl;
        return false;
    }
    for(auto it = ordine.begin(); !it.isPastTheEnd(); ++it) {
        if ((it.firstInfo())->getNome() == prod->getNome()) {   //controllo che il nome del prodotto sia uguale a quello in ordine
            return true;
        }
    }
    std::cerr << "isMember: Il prodotto non è presente nell'ordine." << std::endl;
    return false;
}

void comanda::aggiungiProdotto(prodotto* prod) {
    // Cerca il prodotto
    // Se il prodotto è già presente, incrementa il numero di occorrenze
    if (isMember(prod)) {
        for (auto it = ordine.begin(); !it.isPastTheEnd(); ++it) {
            if ((it.firstInfo())->getNome() == prod->getNome()) {   //controllo che il nome del prodotto sia uguale a quello in ordine
                
                auto second = it.secondInfo();  //salvo prima di eliminare
                ordine.remove(it.firstInfo());
                ordine.insert(prod, second + 1);
                break;
            }
        }
    } else {
    // Altrimenti, aggiungi il prodotto ad ordine
        //controllo che esista
        auto tipo = typeid(*prod).name();
        std::string toPass;
        if (tipo == typeid(bevanda).name()) {
            toPass = "bevanda";
        }
        else if (tipo == typeid(pietanza_cucina).name()) {
            toPass = "pietanza_cucina";
        }
        else if (tipo == typeid(pietanza_griglie).name()) {
            toPass = "pietanza_griglie";
        }
        if(prodotto::exists(prod->getNome(), toPass, pathManager::getPath("prodotti")))
            ordine.insert(prod, 1);
        else
            std::cerr << "Il prodotto non esiste." << std::endl;
    }
}

bool comanda::rimuoviProdotto(prodotto* prod) {
    bool moreThanOne = false;   //true se il prodotto ha più occorrenze
    
    //scorro ordine e cerco il prodotto
    for(auto it = ordine.begin(); !it.isPastTheEnd(); ++it) {
        if ((it.firstInfo())->getNome() == prod->getNome()) {   //controllo che il nome del prodotto sia uguale a quello in ordine
            
            if(it.secondInfo() > 1) moreThanOne = true;
            
            auto second = it.secondInfo();  //salvo prima di eliminare
            ordine.remove(it.firstInfo());

            if(moreThanOne) ordine.insert(prod, second - 1);

            return true;
        }
    }
    return false;
}

std::vector<prodotto*> comanda::getProdotti() const {
    std::vector<prodotto*> prodotti;
    if(!ordine.isEmpty()) {       
        for(auto it = ordine.begin(); !it.isPastTheEnd(); ++it) {
            prodotti.push_back(it.firstInfo());
        }
    } else { //creo un prodotto* nullptr e lo inserisco
        prodotto* p = nullptr;
        prodotti.push_back(p);
    }
    return prodotti;
}

int comanda::getNumeroOccorrenzeProdotto(prodotto* prod) const {
    if (!isMember(prod)) {
        std::cerr << "Il prodotto non è presente nell'ordine." << std::endl;
        return -1;
    }
    auto it = ordine.find(prod);
    int oc = it.secondInfo();       //numero occorrenze
    return oc;
}

float comanda::calcolaTotale() const{
    float tot=0;
    if(!ordine.isEmpty()) {
        for(auto it = ordine.begin(); !it.isPastTheEnd(); ++it) {
            prodotto* prod = it.firstInfo();
            int quantita = it.secondInfo();
            float prezzoPorzione = prod->getPrezzoPorzione();

            tot += quantita * prezzoPorzione;
        }
    }
    return tot;
}

void comanda::serialize(Json::Value& root) const {
    Json::Value comandaJson;
    
    comandaJson["numero"] = num;
    comandaJson["cameriere"] = cameriere->getUsername();
    comandaJson["distributore"] = distributore->getUsername();
    comandaJson["asporto"] = asporto;  

    if(!ordine.isEmpty()) {
        for(auto it = ordine.begin(); !it.isPastTheEnd(); ++it) {
            prodotto *prod = it.firstInfo();
            int numeroOccorrenze = it.secondInfo();

            Json::Value prodottoJson;
            
            if(dynamic_cast<bevanda*>(prod)) {              //all'interno dell'ordine per ogni prodotto salvo sollo il tipo e il numero di occorrenze
                prodottoJson["tipo"] = "bevanda";           //per gli altri campi si andrà a ricercare all'interno di prodotti.json
                prodottoJson["nome"] = prod->getNome();
            }
            else if (dynamic_cast<pietanza_cucina*>(prod)) {
                prodottoJson["tipo"] = "pietanza_cucina";
                prodottoJson["nome"] = prod->getNome();
            }
            else if (dynamic_cast<pietanza_griglie*>(prod)) {
                prodottoJson["tipo"] = "pietanza_griglie";
                prodottoJson["nome"] = prod->getNome();
            }
            prodottoJson["numeroOccorrenze"] = numeroOccorrenze;

            comandaJson["ordine"].append(prodottoJson);
        }
    } else std::cerr << "Comanda - Serialize: Non sono presenti prodotti." << std::endl;

    root["comande"].append(comandaJson);
}

comanda* comanda::deserialize(const Json::Value& root, const Json::Value& userJson, const Json::Value& prodottoJson, int numero){
    for(const auto& comandaJson : root["comande"]) {
        
        if(comandaJson["numero"].asInt() == numero) {

            user* cam = user::deserialize(userJson, comandaJson["cameriere"].asString());
            user* distr = user::deserialize(userJson, comandaJson["distributore"].asString());

            bool asp = comandaJson["asporto"].asBool();

            comanda* c = new comanda(numero, cam, distr, asp);
            
            for (const auto& it : comandaJson["ordine"]) {
                prodotto* prod = nullptr;

                if (it["tipo"].asString() == "bevanda") {
                    prod = bevanda::deserialize(prodottoJson, it["nome"].asString());   //mi prende il prodotto con quel nome dal file json dei prodotti
                }
                else if (it["tipo"].asString() == "pietanza_cucina") {
                    prod = pietanza_cucina::deserialize(prodottoJson, it["nome"].asString());
                }
                else if (it["tipo"].asString() == "pietanza_griglie") {
                    prod = pietanza_griglie::deserialize(prodottoJson, it["nome"].asString());
                }
                int numeroOccorrenze = it["numeroOccorrenze"].asInt();
                
                c->ordine.insert(prod, numeroOccorrenze);
            }
            return c;
        }
    }
    return nullptr;
}

void comanda::save() const {
    //se esiste già una comanda con quel numero la rimuoviamo
    if(exists(num))
        remove(num);
    JsonFileManager jfm(pathManager::getPath("comande"));
    Json::Value comandaJson = jfm.readJsonFile();

    serialize(comandaJson);

    jfm.writeJsonFile(comandaJson);
}



comanda* comanda::load(int numero) {
    JsonFileManager jfm(pathManager::getPath("comande"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return nullptr;

    JsonFileManager jfmUser(pathManager::getPath("users"));
    Json::Value userJson = jfmUser.readJsonFile();

    JsonFileManager jfmProd(pathManager::getPath("prodotti"));
    Json::Value prodottoJson = jfmProd.readJsonFile();

    return deserialize(root, userJson, prodottoJson, numero);
}

void comanda::remove(int removeNum) {
    JsonFileManager jfm(pathManager::getPath("comande"));
    Json::Value root = jfm.readJsonFile();
    if(root.isNull()) return;
    Json::Value& comandeArray = root["comande"];

    Json::Value newComandeArray(Json::arrayValue); //creo un nuovo array di comande

    for(const auto& comandaJson : comandeArray) {
        if(comandaJson["numero"].asInt() != removeNum) { //se il numero della comanda non è uguale a quello della comanda da rimuovere
            newComandeArray.append(comandaJson); //aggiungo la comanda al nuovo array
        }
    }

    root["comande"] = newComandeArray; //sostituisco l'array di comande con quello nuovo

    jfm.writeJsonFile(root);
}

std::vector<comanda*> comanda::loadAll() {
    std::vector<comanda*> comande;

    JsonFileManager jfm(pathManager::getPath("comande"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return comande;

    JsonFileManager jfmUser(pathManager::getPath("users"));
    Json::Value userJson = jfmUser.readJsonFile();

    JsonFileManager jfmProd(pathManager::getPath("prodotti"));
    Json::Value prodottoJson = jfmProd.readJsonFile();

    for(const auto& comandaJson : root["comande"]) {
        comanda *c = deserialize(root, userJson, prodottoJson, comandaJson["numero"].asInt());
        if(c) comande.push_back(c);
    }
    return comande;
}

bool comanda::exists(int numero) {
    JsonFileManager jfm(pathManager::getPath("comande"));
    Json::Value root = jfm.readJsonFile();
    if(root.isNull()) return false;
    Json::Value& comandeArray = root["comande"];

    for(const auto& comandaJson : comandeArray) {
        if(comandaJson["numero"].asInt() == numero) {
            return true;
        }
    }
    return false;
}
