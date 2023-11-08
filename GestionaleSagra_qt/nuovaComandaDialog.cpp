#include "nuovaComandaDialog.h"

nuovaComandaDialog::nuovaComandaDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Nuova Comanda");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;
    setLayout(mainLayout);
    mainLayout->addLayout(formLayout);

    cameriereCB = new QComboBox(this);
    distributoreCB = new QComboBox(this);
    asportoCB = new QComboBox(this);

    formLayout->addRow("Cameriere:", cameriereCB);
    formLayout->addRow("Distributore:", distributoreCB);
    formLayout->addRow("Asporto:", asportoCB);

    std::vector<user*> personale = user::loadAll();
    for(user *u : personale) {
        if(u->getRuolo() == "cameriere")
            cameriereCB->addItem(QString::fromStdString(u->getUsername()));
        else if(u->getRuolo() == "distributore")
            distributoreCB->addItem(QString::fromStdString(u->getUsername()));
    }
    asportoCB->addItem("Si");
    asportoCB->addItem("No");

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &nuovaComandaDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &nuovaComandaDialog::reject);
}

void nuovaComandaDialog::accept() {

    cameriere = user::load(cameriereCB->currentText().toStdString());
    if(cameriere==nullptr) qDebug() << "puntatore cameriere nullo";
    distributore = user::load(distributoreCB->currentText().toStdString());
    if(distributore==nullptr) qDebug() << "puntatore distributore nullo";
    asporto = asportoCB->currentText() == "Si";

    QDialog::accept();
}

user* nuovaComandaDialog::getCameriere() const { return cameriere; }
user* nuovaComandaDialog::getDistributore() const { return distributore; }
bool nuovaComandaDialog::isAsporto() const { return asporto; }
