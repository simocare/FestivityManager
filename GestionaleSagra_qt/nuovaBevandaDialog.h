#ifndef NUOVABEVANDADIALOG_H
#define NUOVABEVANDADIALOG_H

#include "nuovoProdottoDialog.h"

class nuovaBevandaDialog : public nuovoProdottoDialog
{
    Q_OBJECT

public:
    nuovaBevandaDialog(QWidget *parent = nullptr);

    float getVolumeUnit() const;
    bool haAlcool() const;
    bool haCaffeina() const;
    bool isZero() const;

private:
    QLineEdit *volumeLineEdit;
    QComboBox *alcoolComboBox;
    QComboBox *caffeinaComboBox;
    QComboBox *zeroComboBox;

private slots:
    virtual void accept() override;
};

#endif // NUOVABEVANDADIALOG_H
