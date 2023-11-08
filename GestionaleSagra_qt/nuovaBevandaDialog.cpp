#include "nuovaBevandaDialog.h"

nuovaBevandaDialog::nuovaBevandaDialog(QWidget *parent) : nuovoProdottoDialog(parent)
{
    setWindowTitle("Aggiungi Bevanda");

    // Inizializzazione di tutti i campi specifici per la bevanda
    volumeLineEdit = new QLineEdit(this);
    alcoolComboBox = new QComboBox(this);
    alcoolComboBox->addItem("True");
    alcoolComboBox->addItem("False");
    caffeinaComboBox = new QComboBox(this);
    caffeinaComboBox->addItem("True");
    caffeinaComboBox->addItem("False");
    zeroComboBox = new QComboBox(this);
    zeroComboBox->addItem("True");
    zeroComboBox->addItem("False");

    // Aggiungi campi specifici per la bevanda

    // Campi specifici per la bevanda
    formLayout->addRow("Volume unitario (litri):", volumeLineEdit);
    formLayout->addRow("Contiene Alcool:", alcoolComboBox);
    formLayout->addRow("Contiene caffeina:", caffeinaComboBox);
    formLayout->addRow("Bevanda zero:", zeroComboBox);

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &nuovaBevandaDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &nuovaBevandaDialog::reject);
}

float nuovaBevandaDialog::getVolumeUnit() const { return volumeLineEdit->text().toFloat(); }

bool nuovaBevandaDialog::haAlcool() const {
    QString selectedText = alcoolComboBox->currentText();
    return selectedText == "True";
}

bool nuovaBevandaDialog::haCaffeina() const {
    QString selectedText = caffeinaComboBox->currentText();
    return selectedText == "True";
}

bool nuovaBevandaDialog::isZero() const {
    QString selectedText = zeroComboBox->currentText();
    return selectedText == "True";
}

void nuovaBevandaDialog::accept()
{
    bool validFields = true; // Indica se tutti i campi sono validi

    // Validazione del campo Nome
    QString nome = nomeLineEdit->text();
    if (nome.isEmpty()) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Nome non può essere vuoto.");
    }

    //Controllo che non sia già presente in prodotti.json
    if(prodotto::exists(nome.toStdString(), "bevanda", pathManager::getPath("prodotti")))
        QMessageBox::warning(this, "Errore", "È già presente un prodotto con questo nome");

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

    // Validazione del campo Volume Unitario
    bool validVolume = false;
    float volume = volumeLineEdit->text().toFloat(&validVolume);
    if (!validVolume || volume <= 0) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Volume Unitario deve essere un numero maggiore di zero.");
    }

    //i campi con scelte true o false saranno validi

    // Se tutti i campi sono validi, chiudi il dialogo
    if (validFields) {
        QDialog::accept();
    }
}
