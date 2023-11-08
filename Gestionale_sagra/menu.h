#ifndef MENU_H
#define MENU_H

#include "bevanda.h"
#include "pietanza_cucina.h"
#include "pietanza_griglie.h"
#include "myContainer.h"
#include "pathManager.h"
#include "jsonFileManager.h"

class menu {
private:
    myContainer<std::string, std::string> prodotti; //nome, tipo
    
    void serialize(Json::Value&) const;
    static menu* deserialize(const Json::Value& root);
    
public:
    menu();
    menu(const menu&);
    //distruttore di menu è quello di default

    int aggiungiProdotto(const std::string& nome, const std::string& tipo);
    
    void rimuoviProdotto(const std::string& nome);

    //ritorna un vettore di stringhe con tutti i tipi
    const std::vector<std::string*> getTipi() const;

    //ritorna un vettore di stringhe con tutti i nomi di un certo tipo
    const std::vector<std::string*> getProdotti(const std::string& tipo) const;

    //metodo per salvare il menu su file
    void save() const;
    //metodo per caricare il menu da file
    static menu* load();
};

#endif