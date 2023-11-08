 #include "nuovoUserDialog.h"

nuovoUserDialog::nuovoUserDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Aggiungi Personale");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;
    setLayout(mainLayout);

    mainLayout->addLayout(formLayout);

    usernameLineEdit = new QLineEdit(this);
    ruoloComboBox = new QComboBox(this);
    ruoloComboBox->addItem("cameriere");
    ruoloComboBox->addItem("distributore");

    formLayout->addRow("Username", usernameLineEdit);
    formLayout->addRow("Ruolo", ruoloComboBox);

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &nuovoUserDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &nuovoUserDialog::reject);
}

void nuovoUserDialog::accept()
{
    bool validFields = true;

    // Validazione del campo Username
    QString uname = usernameLineEdit->text();
    if (uname.isEmpty()) {
        validFields = false;
        QMessageBox::warning(this, "Errore", "Il campo Username non può essere vuoto.");
    }

    //non serve validare la combobox

    if (validFields) QDialog::accept();
}

QString nuovoUserDialog::getUsername() const { return usernameLineEdit->text(); }

QString nuovoUserDialog::getRuolo() const { return ruoloComboBox->currentText(); }

