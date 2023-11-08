#include "modificaUserDialog.h"

modificaUserDialog::modificaUserDialog(user *existingUser, QWidget *parent) : QDialog(parent)
{
    usr = existingUser;

    QFormLayout *formLayout = new QFormLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addLayout(formLayout);

    usernameLabel = new QLabel(this);
    ruoloComboBox = new QComboBox(this);
    ruoloComboBox->addItem("cameriere");
    ruoloComboBox->addItem("distributore");

    usernameLabel->setText(QString::fromStdString(usr->getUsername()));
    ruoloComboBox->setCurrentText(QString::fromStdString(usr->getRuolo()));

    formLayout->addRow("Nome:", usernameLabel);
    formLayout->addRow("Ruolo:", ruoloComboBox);

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &modificaUserDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &modificaUserDialog::reject);
}

void modificaUserDialog::applyChanges()
{
    usr->setRuolo(getRuolo().toStdString());
}

void modificaUserDialog::accept()
{
    applyChanges();
    QDialog::accept();
}

QString modificaUserDialog::getRuolo() const { return ruoloComboBox->currentText(); }
