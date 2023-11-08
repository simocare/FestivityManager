#ifndef NUOVOPRODOTTODIALOG_H
#define NUOVOPRODOTTODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>

#include "../Gestionale_sagra/prodotto.h"

class nuovoProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    // Metodi per ottenere i dati inseriti dall'utente
    QString getNome() const;
    double getQuantita() const;
    float getPrezzoPorzione() const;

protected:
    //il costruttore può essere invocato solo dalle classi figlie
    nuovoProdottoDialog(QWidget *parent = nullptr);
    QLineEdit *nomeLineEdit;
    QLineEdit *quantitaLineEdit;
    QLineEdit *prezzoPorzioneLineEdit;

    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;

protected slots:
    virtual void accept() override = 0; // Chiamato quando l'utente preme "ok"

};

#endif // NUOVOPRODOTTODIALOG_H
