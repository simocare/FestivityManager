#include "modificaPietanzaCucinaDialog.h"

modificaPietanzaCucinaDialog::modificaPietanzaCucinaDialog(prodotto *existingProd, QWidget *parent) : modificaProdottoDialog(existingProd, parent)
{
    setWindowTitle("Modifica Pietanza Cucina");

    pc = dynamic_cast<pietanza_cucina*>(prod);
    if(!pc) qDebug() << "Il dynamic_cast a pcanda non è andato a buon fine.";

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &modificaPietanzaCucinaDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &modificaPietanzaCucinaDialog::reject);
}

void modificaPietanzaCucinaDialog::applyChanges()
{
    pc->setQuantita(getQuantita());
    pc->setRimanenza(getRimanenza());
    pc->setPrezzoPorzione(getPrezzoPorzione());
}

void modificaPietanzaCucinaDialog::accept()
{
    bool validFields = true;

    // Validazione del campo Nome
    QString nome = nomeLabel->text();
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

    // Validazione del campo Rimanenza
    bool validRimanenza = false;
    double rimanenza = rimanenzaLineEdit->text().toDouble(&validRimanenza);
    if (!validRimanenza || rimanenza < 0 || rimanenza > quantita) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Rimanenza deve essere un numero compreso tra 0 e la Quantità.");
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
        applyChanges();
        QDialog::accept();
    }
}
