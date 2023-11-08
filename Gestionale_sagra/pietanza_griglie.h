#ifndef pietanza_griglie_H
#define pietanza_griglie_H

#include "prodotto.h"

class pietanza_griglie : public prodotto {
private:
    float pesoPorzione;                             //peso in kg per ogni porzione

    virtual void serialize(Json::Value&) const override;
    static pietanza_griglie* deserialize(const Json::Value&, const std::string&);

    friend class comanda;

public:
    pietanza_griglie() = default;
    pietanza_griglie(const std::string& nome, double quantita, double rimanenza, float prezzo, float peso);
    pietanza_griglie(const pietanza_griglie&);
    virtual pietanza_griglie* clone() const override;

    virtual bool operator==(const prodotto&) const override;
    virtual bool operator!=(const prodotto&) const override;

    virtual ~pietanza_griglie() = default;

    float getPeso() const;
    void setPeso(float);

    float getPrezzoKg();

    virtual void stampaRimanenza() override;
    
    static pietanza_griglie* load(const std::string& nome);

    static std::vector<pietanza_griglie*> loadAll();
};

#endif