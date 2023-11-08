#include "nuovaPietanzaCucinaDialog.h"

nuovaPietanzaCucinaDialog::nuovaPietanzaCucinaDialog(QWidget *parent) : nuovoProdottoDialog(parent)
{
    setWindowTitle("Aggiungi Pietanza Cucina");

    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &nuovaPietanzaCucinaDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &nuovaPietanzaCucinaDialog::reject);
}

void nuovaPietanzaCucinaDialog::accept()
{
    bool validFields = true;

    // Validazione del campo Nome
    QString nome = nomeLineEdit->text();
    if (nome.isEmpty()) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Nome non può essere vuoto.");
    }

    // Validazione del campo Quantità
    bool validQuantita = false;
    double quantita = quantitaLineEdit->text().toDouble(&validQuantita);
    if (!validQuantita || quantita <= 0) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Quantità deve essere un numero maggiore di zero.");
    }

    // Validazione del campo Prezzo
    bool validPrezzo = false;
    float prezzoPorzione = prezzoPorzioneLineEdit->text().toFloat(&validPrezzo);
    if (!validPrezzo || prezzoPorzione <= 0) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Prezzo per Porzione deve essere un numero maggiore di zero.");
    }

    // Se tutti i campi sono validi, chiudi il dialogo
    if (validFields) {
        QDialog::accept();
    }
}
