#include "modificaPietanzaGriglieDialog.h"

modificaPietanzaGriglieDialog::modificaPietanzaGriglieDialog(prodotto *existingProd, QWidget *parent) : modificaProdottoDialog(existingProd, parent)
{
    setWindowTitle("Modifica Pietanza Griglie");

    pg = dynamic_cast<pietanza_griglie*>(prod);
    if(!pg) qDebug() << "Il dynamic_cast a pganda non è andato a buon fine.";

    pesoPorzioneLineEdit = new QLineEdit(this);

    pesoPorzioneLineEdit->setText(QString::number(pg->getPeso()));

    formLayout->addRow("Peso porzione (kg)", pesoPorzioneLineEdit);

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &modificaPietanzaGriglieDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &modificaPietanzaGriglieDialog::reject);
}

void modificaPietanzaGriglieDialog::applyChanges() {
    pg->setQuantita(getQuantita());
    pg->setRimanenza(getRimanenza());
    pg->setPrezzoPorzione(getPrezzoPorzione());
    pg->setPeso(getPesoPorzione());
}
void modificaPietanzaGriglieDialog::accept()
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

    //Validazione del campo Peso
    bool validPeso = false;
    float peso = pesoPorzioneLineEdit->text().toFloat(&validPeso);
    if(!validPeso || peso <=0) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Peso deve essere un numero maggiore di zero.");
    }

    if (validFields) {
        applyChanges();
        QDialog::accept();
    }
}

float modificaPietanzaGriglieDialog::getPesoPorzione() const { return pesoPorzioneLineEdit->text().toFloat(); }
