#ifndef COMANDA_H
#define COMANDA_H

#include <iostream>
#include <string>
#include <vector>

#include "user.h"
#include "bevanda.h"
#include "pietanza_cucina.h"
#include "pietanza_griglie.h"
#include "myContainer.h"
#include "pathManager.h"
#include "jsonFileManager.h"

class comanda {
private:
    int num;
    user* cameriere;
    user* distributore;
    bool asporto;                       //true se è da asporto
    myContainer<prodotto *, int> ordine;

virtual void serialize(Json::Value&) const;
    static comanda* deserialize(const Json::Value& root, const Json::Value& userJson, const Json::Value& prodottoJson, int);

public:
    comanda(int numero, user* cameriere, user* distributore, bool asporto);
    comanda(const comanda&);

    int getNumero() const;
    void setNumero(int);

    user* getCameriere() const;
    void setCameriere(user*);

    user* getDistributore() const;
    void setDistributore(user*);

    bool isAsporto() const;
    void setAsporto(bool);

    myContainer<prodotto*, int> getOrdine() const;

    bool isMember(prodotto* prod) const;
    void aggiungiProdotto(prodotto* prod);
    bool rimuoviProdotto(prodotto* prod);      //ritorna 0 se è andata a buon fine, 1 se il prodotto non è stato trovato
    std::vector<prodotto*> getProdotti() const;

    int getNumeroOccorrenzeProdotto(prodotto* prod) const;

    float calcolaTotale() const;

    friend bevanda* bevanda::deserialize(const Json::Value&, const std::string&);

    void save() const;

    static void remove(int);

    static comanda* load(int);
    static std::vector<comanda*> loadAll();

    static bool exists(int);
};

#endif
