#ifndef BEVANDA_H
#define BEVANDA_H

#include "prodotto.h"

class bevanda : public prodotto {
private:
    float volume_unit;              //volume di liquido per unità
    bool alcool;                    //1 se la bevanda è alcolica
    bool caffeina;                  //1 se la bevanda contiene caffeina
    bool zero;                      //1 se la bevanda è "zero" zuccheri

    virtual void serialize(Json::Value&) const override;
    static bevanda* deserialize(const Json::Value&, const std::string&);

    friend class comanda;

public:
    bevanda() = default;
    bevanda(const std::string& nome, double quantita, double rimanenza, float prezzo, float volume, bool alcool, bool caffeina, bool zero);
    bevanda(const bevanda&);
    virtual bevanda* clone() const override;

    virtual bool operator==(const prodotto&) const override;
    virtual bool operator!=(const prodotto&) const override;

    virtual ~bevanda() = default;

    float getPrezzoLitro() const;
    
    float getVolumeUnit() const;
    
    bool haAlcool() const;
    bool haCaffeina() const;
    bool isZero() const;

    void setVolumeUnit(float volume);
    void setAlcool(bool valore);
    void setCaffeina(bool valore);
    void setZero(bool valore);

    virtual void stampaRimanenza() override;

    static bevanda* load(const std::string& nome);

    static std::vector<bevanda*> loadAll();
};

#endif