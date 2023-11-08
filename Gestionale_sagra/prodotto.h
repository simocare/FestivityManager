#ifndef PRODOTTO_H
#define PRODOTTO_H

#include <string>
#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include "jsonFileManager.h"
#include "pathManager.h"

class prodotto {
private:
    std::string nome;
    std::set<std::string> allergeni;
    double quantita;                        //quantità totale del prodotto
    double rimanenza;                       //quantità rimanente del prodotto
    float prezzoPorzione;                   //prezzo per ogni porzione

protected:
    virtual void serialize(Json::Value&) const;
    //non c'è il deserialize perché non posso istanziare un nuovo prodotto e restituirlo,
    //perché classe base astratta

public:
    prodotto() = default;
    prodotto(const std::string& nome, double quantita, double rimanenza, float prezzo);
    prodotto(const prodotto&);
    virtual prodotto* clone() const = 0;

    virtual bool operator==(const prodotto&) const = 0;
    virtual bool operator!=(const prodotto&) const = 0;

    virtual ~prodotto() = default;
    
    std::string getNome() const;
    void setNome(const std::string& nuovoNome);
    
    void aggiungiAllergene(const std::string&);
    void rimuoviAllergene(const std::string&);
    bool contieneAllergene(const std::string&) const;
    const std::set<std::string>& getAllergeni() const;

    double getQuantita() const;
    void setQuantita(double);
    double getRimanenza() const;
    void setRimanenza(double);
    void aumentaRimanenza(double);
    void diminuisciRimanenza(double);

    float getPrezzoPorzione() const;
    void setPrezzoPorzione(float);

    virtual void stampaRimanenza() = 0;

    //metodo per salvare un prodotto nel file json in "append"
    void save() const;
    //metodo per caricare statico, viene definito su ogni classe figlia

    //ritorna 1 se esiste un prodotto con quel nome, 0 altrimenti
    static int exists(const std::string& nome, const std::string& tipo, const std::string& fileName);

    //metodo che elimina un prodotto dal file json
    static void remove(const std::string& nome, const std::string& tipo);
};

#endif
