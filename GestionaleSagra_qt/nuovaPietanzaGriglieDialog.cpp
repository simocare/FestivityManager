#include "nuovaPietanzaGriglieDiealog.h"

nuovaPietanzaGriglieDialog::nuovaPietanzaGriglieDialog(QWidget *parent) : nuovoProdottoDialog(parent)
{
    setWindowTitle("Aggiungi Pietanza Griglie");

    // Inizializzazione di tutti i campi specifici per la pietanza griglie
    pesoPorzioneLineEdit = new QLineEdit(this);

    // Aggiungi campi specifici per la pietanza griglie

    // Campi specifici per la pietanza griglie
    formLayout->addRow("Peso (grammi):", pesoPorzioneLineEdit);

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &nuovaPietanzaGriglieDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &nuovaPietanzaGriglieDialog::reject);
}

float nuovaPietanzaGriglieDialog::getPesoPorzione() const { return pesoPorzioneLineEdit->text().toFloat(); }

void nuovaPietanzaGriglieDialog::accept()
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

    //Validazione del campo Peso
    bool validPeso = false;
    float peso = pesoPorzioneLineEdit->text().toFloat(&validPeso);
    if(!validPeso || peso <=0) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Peso deve essere un numero maggiore di zero.");
    }

    if (validFields) {
        QDialog::accept();
    }
}
