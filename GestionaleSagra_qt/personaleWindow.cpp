#include "personaleWindow.h"

personaleWindow::personaleWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Gestione personale");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    personaleUI = new QListWidget;

    //impostazione del layout
    setLayout(mainLayout);

    personale = user::loadAll();

    for(const user* u : personale) {
        std::string uname = u->getUsername();
        if(uname != "admin" && uname != "cassiere")
            personaleUI->addItem(QString::fromStdString( uname ));
    }

    mainLayout->addWidget(personaleUI);

    //creazione dei pulsanti di aggiunta e rimozione
    QPushButton *addButton = new QPushButton("Aggiungi", this);
    QPushButton *editButton = new QPushButton("Modifica", this);
    QPushButton *removeButton = new QPushButton("Rimuovi", this);

    //connessione pulsanti
    connect(addButton, &QPushButton::clicked, this, &personaleWindow::onAddButtonClicked);
    connect(editButton, &QPushButton::clicked, this, &personaleWindow::onEditButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &personaleWindow::onRemoveButtonClicked);

    //layout pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(removeButton);

    //aggiunta al layout principale
    mainLayout->addLayout(buttonLayout);
}

void personaleWindow::onAddButtonClicked() {
    nuovoUserDialog udialog(this);
    if(udialog.exec() == QDialog::Accepted) {
        std::string username = udialog.getUsername().toStdString();
        std::string ruolo = udialog.getRuolo().toStdString();

        //creiamo un nuovo user
        user nuovoUser(username, ruolo);

        nuovoUser.save();

        personaleUI->addItem(udialog.getUsername());
    } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessun nuovo utente è stato aggiunto.");
}
void personaleWindow::onEditButtonClicked()
{
    QList<QListWidgetItem*> selectedItems = personaleUI->selectedItems();
    for (QListWidgetItem* selectedItem : selectedItems) {
        std::string selectedItemText = selectedItem->text().toStdString();

        user *u = user::load(selectedItemText);

        modificaUserDialog udialog(u, this);
        if(udialog.exec() == QDialog::Accepted) {
            user::remove(u->getUsername());         //rimuovo
            u->save();                              //aggingo quello nuovo con le modifiche
        } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessuna modifica è stata applicata.");
    }
}
void personaleWindow::onRemoveButtonClicked() {
    QList<QListWidgetItem*> selectedItems = personaleUI->selectedItems();
    for (QListWidgetItem* selectedItem : selectedItems) {
        std::string selectedItemText = selectedItem->text().toStdString();
        user::remove(selectedItemText);

        delete selectedItem;
    }
}
