#ifndef PIETANZA_CUCINA_H
#define PIETANZA_CUCINA_H

#include "prodotto.h"

class pietanza_cucina : public prodotto {
private:
    virtual void serialize(Json::Value&) const override;
    static pietanza_cucina* deserialize(const Json::Value&, const std::string&);

    friend class comanda;

public:
    pietanza_cucina() = default;
    pietanza_cucina(const std::string& nome, double quantita, double rimanenza, float prezzo);
    pietanza_cucina(const pietanza_cucina&);
    virtual pietanza_cucina* clone() const override;

    virtual bool operator==(const prodotto&) const override;
    virtual bool operator!=(const prodotto&) const override;

    virtual ~pietanza_cucina() = default;

    virtual void stampaRimanenza() override;

    static pietanza_cucina* load(const std::string& nome);
    
    static std::vector<pietanza_cucina*> loadAll();
};

#endif