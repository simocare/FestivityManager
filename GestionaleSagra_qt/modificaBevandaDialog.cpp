#include "modificaBevandaDialog.h"

modificaBevandaDialog::modificaBevandaDialog(prodotto* existingProd, QWidget *parent) : modificaProdottoDialog(existingProd, parent)
{
    setWindowTitle("Modifica Bevanda");
    //Determiniamo il tipo dinamico di prod
    bev = dynamic_cast<bevanda*>(prod);
    if(!bev) qDebug() << "Il dynamic_cast a bevanda non è andato a buon fine.";

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

    //carico dati esistenti
    volumeLineEdit->setText(QString::number(bev->getVolumeUnit()));
    alcoolComboBox->setCurrentText(bev->haAlcool() ? "True" : "False");
    caffeinaComboBox->setCurrentText(bev->haCaffeina() ? "True" : "False");
    zeroComboBox->setCurrentText(bev->isZero() ? "True" : "False");

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
    connect(okButton, &QPushButton::clicked, this, &modificaBevandaDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &modificaBevandaDialog::reject);
}
void modificaBevandaDialog::applyChanges()
{
    // Aggiorna i dati nell'oggetto bevanda con i valori dai campi di input
    bev->setQuantita(getQuantita());
    bev->setRimanenza(getRimanenza());
    bev->setPrezzoPorzione(getPrezzoPorzione());
    bev->setVolumeUnit(getVolumeUnit());
    bev->setAlcool(haAlcool());
    bev->setCaffeina(haCaffeina());
    bev->setZero(isZero());
}
void modificaBevandaDialog::accept()
{
    bool validFields = true; // Indica se tutti i campi sono validi

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
        applyChanges();
        QDialog::accept();
    }
}

float modificaBevandaDialog::getVolumeUnit() const { return volumeLineEdit->text().toFloat(); }

bool modificaBevandaDialog::haAlcool() const { return alcoolComboBox->currentText() == "True"; }

bool modificaBevandaDialog::haCaffeina() const { return caffeinaComboBox->currentText() == "True"; }

bool modificaBevandaDialog::isZero() const { return zeroComboBox->currentText() == "True"; }
