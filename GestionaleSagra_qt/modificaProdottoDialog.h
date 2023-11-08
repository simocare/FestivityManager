#ifndef MODIFICAPRODOTTODIALOG_H
#define MODIFICAPRODOTTODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>

#include "../Gestionale_sagra/bevanda.h"
#include "../Gestionale_sagra/pietanza_cucina.h"
#include "../Gestionale_sagra/pietanza_griglie.h"

#include "../Gestionale_sagra/pathManager.h"


class modificaProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    QString getNome() const;
    double getQuantita() const;
    double getRimanenza() const;
    float getPrezzoPorzione() const;

protected:
    modificaProdottoDialog(prodotto* existingProd, QWidget *parent = nullptr);    //passa il prodotto, poi le classi figlie faranno dynamic_cast
    QLabel *nomeLabel;
    QLineEdit *quantitaLineEdit;
    QLineEdit *rimanenzaLineEdit;
    QLineEdit *prezzoPorzioneLineEdit;

    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;

    prodotto *prod;

protected slots:
    virtual void accept() override = 0;
    virtual void applyChanges() = 0;
};

#endif // MODIFICAPRODOTTODIALOG_H
