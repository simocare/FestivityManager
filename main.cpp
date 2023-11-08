#include "comanda.h"
#include "tavolo.h"
#include "menu.h"
#include "jsonFileManager.h"
#include "myContainer.h"

int main() {
    /*
    // Creiamo alcuni utenti (cameriere e distributore)
    user cameriere("Mario Rossi", "mario123", "cameriere");
    user distributore("Luigi Verdi", "luigi456", "distributore");

    // Creiamo alcuni prodotti
    bevanda bev1("Coca-Cola", 2.0, 1.5, 0.5, false, true, true);
    pietanza_cucina piet1("Pizza Margherita", 8.0, 10.0);
    pietanza_griglie piet2("Bistecca", 1.0, 25.0, 0.3);

    // Creiamo una comanda
    comanda com1(1, cameriere, distributore, true);

    // Aggiungiamo alcuni prodotti all'ordine
    com1.aggiungiProdotto(&bev1);
    com1.aggiungiProdotto(&piet1);
    com1.aggiungiProdotto(&piet2);
    com1.aggiungiProdotto(&bev1); // Aggiungiamo lo stesso prodotto più volte

    // Rimuoviamo un prodotto dall'ordine
    bool rimozioneEsito = com1.rimuoviProdotto(&piet1);
    if (rimozioneEsito) {
        std::cout << "Prodotto rimosso dall'ordine." << std::endl;
    } else {
        std::cout << "Il prodotto non è stato trovato nell'ordine." << std::endl;
    }

    // Stampiamo l'ordine
    com1.stampaOrdine();

    // Calcoliamo il totale dell'ordine
    float totale = com1.calcolaTotale();
    std::cout << "Totale dell'ordine: " << totale << " euro" << std::endl;
    */
    
    //Creiamo dei tavoli
    // tavolo tav1(1, 4, true);
    // tavolo tav2(2, 2, true);
    // tavolo tav3(3, 6, false);

    // //Salviamo i tavoli in un file tavoli.json
    // Json::Value root;
    // tav1.serialize(root);
    // tav2.serialize(root);
    // tav3.serialize(root);

    // std::ofstream tavoliFile("tavoli.json");
    // if (tavoliFile.is_open()) {
    //     Json::StreamWriterBuilder builder;
    //     std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
    //     jsonWriter->write(root, &tavoliFile);

    //     tavoliFile.close();
        
    //     if (tavoliFile.good()) {
    //         std::cout << "Scrittura JSON completata con successo." << std::endl;
    //     } else {
    //         std::cerr << "Errore durante la scrittura del file JSON." << std::endl;
    //     }
    // } else {
    //     std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
    // }

    // //Leggiamo i tavoli dal file tavoli.json
    // std::ifstream tavoliFile2("tavoli.json");
    // if (tavoliFile2.is_open()) {
    //     Json::Value root;
    //     Json::CharReaderBuilder builder;
    //     std::string errors;

    //     if (Json::parseFromStream(builder, tavoliFile2, &root, &errors)) {
    //         std::cout << "Lettura JSON completata con successo." << std::endl;

    //         //Stampiamo i tavoli
    //         for (const auto& tJson : root["tavoli"]) {
    //             std::cout << "Tavolo:" << std::endl;
    //             tavolo* tav;
    //             tav = tavolo::deserialize(root, tJson["id"].asInt());
    //             if(tav) {
    //                 tav->stampaTavolo();
    //                 delete tav;
    //             }
    //         }
    //     } else {
    //         std::cerr << "Errore durante la lettura del file JSON." << std::endl;
    //     }

    //     tavoliFile2.close();
    // } else {
    //     std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
    // }

    //Creiamo degli utenti
    // user utente1("Mario Rossi", "mario123", "cameriere");
    // user utente2("Luigi Verdi", "luigi456", "distributore");
    // user utente3("Giovanni Bianchi", "giovanni789", "cameriere");

    // //Salviamo gli utenti in un file users.json
    // Json::Value root;
    // utente1.serialize(root);
    // utente2.serialize(root);
    // utente3.serialize(root);

    // std::ofstream usersFile("users.json");
    // if (usersFile.is_open()) {
    //     Json::StreamWriterBuilder builder;
    //     std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
    //     jsonWriter->write(root, &usersFile);

    //     usersFile.close();
        
    //     if (usersFile.good()) {
    //         std::cout << "Scrittura JSON completata con successo." << std::endl;
    //     } else {
    //         std::cerr << "Errore durante la scrittura del file JSON." << std::endl;
    //     }
    // } else {
    //     std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
    // }

    //Leggiamo gli utenti dal file users.json
    // Json::Value rootU;
    // std::ifstream usersFile2("users.json");
    // if (usersFile2.is_open()) {

    //     Json::CharReaderBuilder builderU;
    //     std::string errorsU;

    //     if (Json::parseFromStream(builderU, usersFile2, &rootU, &errorsU)) {
    //         std::cout << "Lettura JSON completata con successo." << std::endl;

    //         //Stampiamo gli utenti
    //         for (const auto& uJson : rootU["users"]) {
    //             std::cout << "Utente:" << std::endl;
    //             user* utente = user::deserialize(rootU, uJson["username"].asString());
    //             if(utente) {
    //                 std::cout << "Username: " << utente->getUsername() << std::endl;
    //                 std::cout << "Ruolo: " << utente->getRuolo() << std::endl;
    //                 delete utente;
    //             }
    //         }
    //     } else {
    //         std::cerr << "Errore durante la lettura del file JSON." << std::endl;
    //     }

    //     usersFile2.close();
    // } else {
    //     std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
    // }

    // //Creiamo dei prodotti
    // bevanda bev1("Coca Cola", 30, 2.5, 0.33, false, true, false);
    // bevanda bev2("Fanta", 30, 2.5, 0.33, false, true, false);
    // pietanza_cucina pi1("Pasticcio", 15, 7);
    // pietanza_griglie pi2("Costicine", 40.5, 5, 0.2);

    //Salviamo i prodotti in un file prodotti.json
    // Json::Value root;
    // bev1.serialize(root);
    // bev2.serialize(root);
    // pi1.serialize(root);
    // pi2.serialize(root);
    
    // std::ofstream prodottiFile("prodotti.json");
    // if (prodottiFile.is_open()) {
    //     Json::StreamWriterBuilder builder;
    //     std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
    //     jsonWriter->write(root, &prodottiFile);

    //     prodottiFile.close();
        
    //     if (prodottiFile.good()) {
    //         std::cout << "Scrittura JSON completata con successo." << std::endl;
    //     } else {
    //         std::cerr << "Errore durante la scrittura del file JSON." << std::endl;
    //     }
    // } else {
    //     std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
    // }

    //Leggiamo i prodotti dal file prodotti.json
    // Json::Value rootP;
    // std::ifstream prodottiFile2("prodotti.json");
    // if (prodottiFile2.is_open()) {

    //     Json::CharReaderBuilder builderP;
    //     std::string errorsP;

    //     if (Json::parseFromStream(builderP, prodottiFile2, &rootP, &errorsP)) {
    //         std::cout << "Lettura JSON completata con successo." << std::endl;

    //         //Stampiamo i prodotti
    //         for (const auto& pJson : rootP["prodotti"]) {
    //             std::cout << "Prodotto:" << std::endl;
                
    //             if(pJson["tipo"].asString() == "bevanda") {
    //                 bevanda* bev = bevanda::deserialize(rootP, pJson["nome"].asString());
    //                 std::cout << "Nome: " << bev->getNome() << std::endl;
    //                 std::cout << "Caffeina: " << bev->haCaffeina() << std::endl;
    //                 delete bev;
    //             }
    //             else if(pJson["tipo"].asString() == "pietanza_cucina") {
    //                 pietanza_cucina* pi = pietanza_cucina::deserialize(rootP, pJson["nome"].asString());
    //                 std::cout << "Nome: " << pi->getNome() << std::endl;
    //                 delete pi;
    //             }
    //             else if(pJson["tipo"].asString() == "pietanza_griglie") {
    //                 pietanza_griglie* pi = pietanza_griglie::deserialize(rootP, pJson["nome"].asString());
    //                 std::cout << "Nome: " << pi->getNome() << std::endl;
    //                 std::cout << "Peso: " << pi->getPeso() << std::endl;
    //                 delete pi;
    //             }
    //         }
    //     } else {
    //         std::cerr << "Errore durante la lettura del file JSON." << std::endl;
    //     }

    //     prodottiFile2.close();
    // } else {
    //     std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
    // }

    // //Creiamo delle comande
    // comanda com1(1, &utente1, &utente2, false);
    // com1.aggiungiProdotto(&bev1);
    // com1.aggiungiProdotto(&bev2);
    // com1.aggiungiProdotto(&pi1);
    // comanda com2(2, &utente3, &utente2, false);
    // com2.aggiungiProdotto(&pi2);
    // com2.aggiungiProdotto(&bev1);

    // //Salviamo le comande in un file comande.json
    // Json::Value rootC;
    // com1.serialize(rootC);
    // com2.serialize(rootC);

    // std::ofstream comandeFile("comande.json");
    // if (comandeFile.is_open()) {
    //     Json::StreamWriterBuilder builder;
    //     std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
    //     jsonWriter->write(rootC, &comandeFile);

    //     comandeFile.close();
        
    //     if (comandeFile.good()) {
    //         std::cout << "Scrittura JSON completata con successo." << std::endl;
    //     } else {
    //         std::cerr << "Errore durante la scrittura del file JSON." << std::endl;
    //     }
    // } else {
    //     std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
    // }

    // //Leggiamo le comande dal file comande.json
    // std::ifstream comandeFile2("comande.json");
    // if (comandeFile2.is_open()) {
    //     Json::CharReaderBuilder builderC;
    //     std::string errorsC;

    //     if (Json::parseFromStream(builderC, comandeFile2, &rootC, &errorsC)) {
    //         std::cout << "Lettura JSON completata con successo." << std::endl;

    //         //Stampiamo le comande
    //         for (const auto& cJson : rootC["comande"]) {
    //             std::cout << "Comanda:" << std::endl;
    //             comanda* com = comanda::deserialize(rootC, rootU, rootP,  cJson["numero"].asInt());

    //             std::cout << "Numero: " << com->getNumero() << std::endl;
    //             std::cout << "Cameriere: " << com->getCameriere()->getUsername() << std::endl;
    //             std::cout << "Distributore: " << com->getDistributore()->getUsername() << std::endl;
    //             std::cout << "Ordine:" << std::endl;
    //             for (const auto& pJson : cJson["ordine"]) {
    //                 if(pJson["tipo"].asString() == "bevanda") {
    //                     bevanda* bev = bevanda::deserialize(rootP, pJson["nome"].asString());
    //                     std::cout << "Nome: " << bev->getNome() << std::endl;
    //                     std::cout << "Caffeina: " << bev->haCaffeina() << std::endl;
    //                     std::cout << "Alcolica: " << bev->haAlcool() << std::endl;
    //                     std::cout << "Zero: " << bev->isZero() << std::endl;
    //                     delete bev;
    //                 }
    //                 else if(pJson["tipo"].asString() == "pietanza_cucina") {
    //                     pietanza_cucina* pi = pietanza_cucina::deserialize(rootP, pJson["nome"].asString());
    //                     std::cout << "Nome: " << pi->getNome() << std::endl;
    //                     delete pi;
    //                 }
    //                 else if(pJson["tipo"].asString() == "pietanza_griglie") {
    //                     pietanza_griglie* pi = pietanza_griglie::deserialize(rootP, pJson["nome"].asString());
    //                     std::cout << "Nome: " << pi->getNome() << std::endl;
    //                     std::cout << "Peso: " << pi->getPeso() << std::endl;
    //                     delete pi;
    //                 }
    //             }
    //             //delete com;
    //         }
    //     } else {
    //         std::cerr << "Errore durante la lettura del file JSON." << std::endl;
    //     }

    //     comandeFile2.close();
    // } else {
    //     std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
    // }

    // //Creiamo dei menu
    // menu menu1;
    // menu1.aggiungiBevanda("Coca Cola");
    // menu1.aggiungiBevanda("Fanta");
    // menu1.aggiungiPietanzaCucina("Pasticcio");
    // menu1.aggiungiPietanzaGriglie("Costicine");

    // menu1.stampaMenu();
    // menu1.rimuoviBevanda("Coca Cola");
    // menu1.aggiungiBevanda("Sprite");
    // std::cout << "dopo modifica" << std::endl;
    // menu1.stampaMenu();

    // //Salviamo i menu in un file menu.json
    // Json::Value rootM;
    // menu1.serialize(rootM);

    // std::ofstream menuFile("menu.json");
    // if (menuFile.is_open()) {
    //     Json::StreamWriterBuilder builder;
    //     std::unique_ptr<Json::StreamWriter> jsonWriter(builder.newStreamWriter());
    //     jsonWriter->write(rootM, &menuFile);

    //     menuFile.close();
        
    //     if (menuFile.good()) {
    //         std::cout << "Scrittura JSON completata con successo." << std::endl;
    //     } else {
    //         std::cerr << "Errore durante la scrittura del file JSON." << std::endl;
    //     }
    // } else {
    //     std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
    // }

    // //Leggiamo il menu dal file menu.json
    // std::ifstream menuFile2("menu.json");
    // if (menuFile2.is_open()) {
    //     Json::CharReaderBuilder builderM;
    //     std::string errorsM;

    //     if (Json::parseFromStream(builderM, menuFile2, &rootM, &errorsM)) {
    //         std::cout << "Lettura JSON completata con successo." << std::endl;

    //         //Stampiamo il menu
    //             std::cout << "Menu:" << std::endl;
    //             menu* menu = menu::deserialize(rootM);

    //             std::cout << "Bevande:" << std::endl;
    //             for (const auto& bevanda : menu->getBevande()) {
    //                 std::cout << *bevanda << std::endl;
    //             }
    //             std::cout << std::endl << "Pietanze cucina:" << std::endl;
    //             for (const auto& pietanza_cucina : menu->getPietanzeCucina()) {
    //                 std::cout << *pietanza_cucina << std::endl;
    //             }
    //             std::cout << std::endl << "Pietanze griglie:" << std::endl;
    //             for (const auto& pietanza_griglie : menu->getPietanzeGriglie()) {
    //                 std::cout << *pietanza_griglie << std::endl;
    //             }
    //             delete menu;
    //     } else {
    //         std::cerr << "Errore durante la lettura del file JSON." << std::endl;
    //     }

    //     menuFile2.close();
    // } else {
    //     std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
    // }

    // //Facciamo un test di jsonFileManager con il file menu.json
    // JsonFileManager jfm("menu.json");
    // Json::Value rootJFM = jfm.readJsonFile();
    // std::cout << "Stampa del file menu.json:" << std::endl;
    // std::cout << rootJFM << std::endl;

    // //aggiungiamo un prodotto al menu
    // menu1.aggiungiBevanda("Spuma");
    // //scriviamo il menu nel file
    // menu1.serialize(rootJFM);

    // jfm.writeJsonFile(rootJFM);
    // //rileggiamo il file per vedere se è stato modificato
    // rootJFM = jfm.readJsonFile();
    // std::cout << "Stampa del file menu.json dopo la scrittura:" << std::endl;
    // std::cout << rootJFM << std::endl;

    // //test di exists
    // std::cout << "Test di exists:" << std::endl;
    // std::cout << "Esiste la bevanda Coca Cola? " << prodotto::exists("Coca Cola", "bevanda", "prodotti.json") << std::endl;

    // //test di aggiungiBevanda
    // std::cout << "Test di aggiungiBevanda con bevanda inesistente:" << std::endl;
    // menu1.aggiungiBevanda("ColaCoca");

    //test della classe myContainer
    // myContainer<std::string, int> container;
    // container.insert("ciao", 1);
    // container.insert("come", 2);
    // container.insert("stai", 3);
    // container.insert("?", 4);

    // std::cout << "Stampa del container:" << std::endl;
    // for(auto it = container.begin(); !it.isPastTheEnd(); ++it) {
    //     std::cout << it.firstInfo() << " " << it.secondInfo() << std::endl;
    // }

    //     //test metodo end() di myContainer
    // std::cout << "Test del metodo end() di myContainer:" << std::endl;
    // //stampa firstInfo dell'ultimo elemento col metodo end()
    // std::cout << container.end().firstInfo() << std::endl;

    // //test della classe menu in tutti i suoi metodi
    // menu* menu1 = menu::load();
    // menu1->aggiungiProdotto("Coca Cola", "bevanda");
    
    // //scrittura del menu su file
    // menu1->save();

    //test di save e load di bevanda
    // bevanda* bev = bevanda::load("Coca Cola");
    // if(bev) {
    //     bev->stampaRimanenza();
    //     bev->setRimanenza(20);
    //     bev->stampaRimanenza();
    //     bev->save();
    // }

    //test di save e load di pietanza_cucina
    // pietanza_cucina* pi = pietanza_cucina::load("Pasticcio");
    // if(pi) {
    //     std::cout << pi->getRimanenza() << std::endl;
    //     pi->stampaRimanenza();
    //     pi->setRimanenza(10);
    //     pi->stampaRimanenza();
    //     pi->save();
    // }

    // //test di save e load di pietanza_griglie
    // pietanza_griglie* pi2 = pietanza_griglie::load("Costicine");
    // if(pi2) {    
    //     pi2->stampaRimanenza();
    //     pi2->setRimanenza(30);
    //     pi2->stampaRimanenza();
    //     pi2->save();
    // }

    //test di loadAll di bevanda
    // std::vector<bevanda*> bevande = bevanda::loadAll();
    // for(const auto& bev : bevande) {
    //     std::cout << bev->getNome() << std::endl;
    //     delete bev;
    // }

    // //eliminiamo la bevanda sangue
    // prodotto::remove("sangue", "bevanda", "prodotti.json");

    //test di save e load di user
    // user* utente = user::load("Mario Rossi");
    // if(utente) {
    //     std::cout << utente->getUsername() << std::endl;
    //     std::cout << utente->getPassword() << std::endl;
    //     std::cout << utente->getRuolo() << std::endl;
    //     utente->setPassword("mario1234");
    //     utente->setRuolo("distributore");
    //     utente->save();
    // }

    //test dei metodi di comanda
    // comanda* com = comanda::load(4);

    // if(com) {
    //     // std::cout << com->getNumero() << std::endl;
    //     // std::cout << com->getCameriere()->getUsername() << std::endl;
    //     // std::cout << com->getDistributore()->getUsername() << std::endl;
    //     // std::cout << com->isAsporto() << std::endl;
    //     //com->setAsporto(false);
    //     //com->save();

    //     //stampiamo il numero delle comande

    //     //aggiungiamo un prodotto
    //     bevanda *bev = bevanda::load("Coca Cola");

    //     //stampiamo il numero delle comande
    //     std::vector<comanda*> comande3 = comanda::loadAll();
    //     std::cout << "Numero comande: " << comande3.size() << std::endl;

    //     if(bev) {
    //         com->aggiungiProdotto(bev);
    //         com->aggiungiProdotto(bev);
    //         com->save();
    //         com->rimuoviProdotto(bev);
    //         com->save();
    //     }

    // }

    //test di myContainer::find
    // std::cout << "Test di myContainer::find" << std::endl;
    // myContainer<std::string, int> container;
    // container.insert("ciao", 1);
    // container.insert("come", 2);

    // auto it = container.find("ciao");
    // std::cout << it.firstInfo() << " " << it.secondInfo() << std::endl;

    //test di comanda::loadAll
    // std::cout << "Test di comanda::loadAll" << std::endl;
    // std::vector<comanda*> comande = comanda::loadAll();
    // for(const auto& com : comande) {
    //     std::cout << com->getNumero() << std::endl;
    //     std::cout << com->getCameriere()->getUsername() << std::endl;
    //     std::cout << com->getDistributore()->getUsername() << std::endl;
    //     std::cout << com->isAsporto() << std::endl;
    //     delete com;
//}

//creo una comanda coi dei prodotti
user* u1 = new user("Mario Rossi", "cameriere", "");
user* u2 = new user("Luigi Verdi", "distributore", "");
user utente3("Giovanni Bianchi", "cameriere", "");

std::cout << u1->getRuolo() << std::endl;

comanda com1(1, u1, u2, false);

bevanda* bev = bevanda::load("Coca Cola");
bevanda* bev2 = bevanda::load("Fanta");

if(bev) {
    com1.aggiungiProdotto(bev);
    com1.aggiungiProdotto(bev);
    com1.aggiungiProdotto(bev2);
}

//test del metodo getNumeroProdotti
std::cout << "Test del metodo getNumeroProdotti" << std::endl;
std::cout << com1.getNumeroOccorrenzeProdotto(bev2) << std::endl;



    return 0;
}