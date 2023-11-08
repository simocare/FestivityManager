#ifndef COMANDAAGGIUNGIPRODOTTODIALOG_H
#define COMANDAAGGIUNGIPRODOTTODIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>

#include "../Gestionale_sagra/comanda.h"
#include "../Gestionale_sagra/bevanda.h"
#include "../Gestionale_sagra/pietanza_cucina.h"
#include "../Gestionale_sagra/pietanza_griglie.h"

class comandaAggiungiProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    comandaAggiungiProdottoDialog(QWidget *parent = nullptr);
    prodotto* getProdotto() const;

private:
    prodotto *prod;
    QComboBox *comboProd;

private slots:
    virtual void accept() override;
};

#endif // COMANDAAGGIUNGIPRODOTTODIALOG_H
