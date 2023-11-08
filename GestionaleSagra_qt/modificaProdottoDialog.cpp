#include "modificaProdottoDialog.h"

modificaProdottoDialog::modificaProdottoDialog(prodotto* existingProd, QWidget *parent) : QDialog(parent)
{
    prod = existingProd;    //inizializzo prodotto

    formLayout = new QFormLayout;
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addLayout(formLayout);

    // Inizializzazione di tutti i campi
    nomeLabel = new QLabel(this);
    quantitaLineEdit = new QLineEdit(this);
    rimanenzaLineEdit = new QLineEdit(this);
    prezzoPorzioneLineEdit = new QLineEdit(this);

    // Carico i dati esistenti dell'oggetto prod
    nomeLabel->setText(QString::fromStdString(prod->getNome()));
    quantitaLineEdit->setText(QString::number(prod->getQuantita()));
    rimanenzaLineEdit->setText(QString::number(prod->getRimanenza()));
    prezzoPorzioneLineEdit->setText(QString::number(prod->getPrezzoPorzione()));

    formLayout->addRow("Nome:", nomeLabel);
    formLayout->addRow("Quantità:", quantitaLineEdit);
    formLayout->addRow("Rimanenza:", rimanenzaLineEdit);
    formLayout->addRow("Prezzo Porzione(€):", prezzoPorzioneLineEdit);
}

QString modificaProdottoDialog::getNome() const { return nomeLabel->text(); }

double modificaProdottoDialog::getQuantita() const { return quantitaLineEdit->text().toDouble(); }

double modificaProdottoDialog::getRimanenza() const { return rimanenzaLineEdit->text().toDouble(); }

float modificaProdottoDialog::getPrezzoPorzione() const { return prezzoPorzioneLineEdit->text().toFloat(); }
