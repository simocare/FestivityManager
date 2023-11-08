#include "nuovoProdottoDialog.h"

nuovoProdottoDialog::nuovoProdottoDialog(QWidget *parent) : QDialog(parent)
{
    formLayout = new QFormLayout;
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addLayout(formLayout);

    // Inizializzazione di tutti i campi specifici per la bevanda
    nomeLineEdit = new QLineEdit(this);
    quantitaLineEdit = new QLineEdit(this);
    prezzoPorzioneLineEdit = new QLineEdit(this);

    formLayout->addRow("Nome:", nomeLineEdit);
    formLayout->addRow("Quantità:", quantitaLineEdit);
    formLayout->addRow("Prezzo Porzione(€):", prezzoPorzioneLineEdit);
}

QString nuovoProdottoDialog::getNome() const { return nomeLineEdit->text(); }

double nuovoProdottoDialog::getQuantita() const { return quantitaLineEdit->text().toDouble(); }

float nuovoProdottoDialog::getPrezzoPorzione() const { return prezzoPorzioneLineEdit->text().toFloat(); }
