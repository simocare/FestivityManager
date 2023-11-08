#ifndef MODIFICABEVANDADIALOG_H
#define MODIFICABEVANDADIALOG_H

#include "modificaProdottoDialog.h"

class modificaBevandaDialog : public modificaProdottoDialog
{
    Q_OBJECT

public:
    modificaBevandaDialog(prodotto* existingProd, QWidget *parent = nullptr);

    float getVolumeUnit() const;
    bool haAlcool() const;
    bool haCaffeina() const;
    bool isZero() const;

private:
    QLineEdit *volumeLineEdit;
    QComboBox *alcoolComboBox;
    QComboBox *caffeinaComboBox;
    QComboBox *zeroComboBox;

    bevanda *bev; //puntatore all'oggetto bevanda

private slots:
    virtual void accept() override;
    virtual void applyChanges() override;
};

#endif // MODIFICABEVANDADIALOG_H
