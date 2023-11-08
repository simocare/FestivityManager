#include "menuWindow.h"

menuWindow::menuWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Menu del giorno");
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //POPOLAMENTO DEL MENU DA JSON
    menuAttuale = menu::load();

    tipi = menuAttuale->getTipi();

    for (const std::string* tipo : tipi) {
        //creo la QListWidget del tipo "taget"
        QListWidget* l = new QListWidget(this);
        std::vector<std::string*> prodottiTipo = menuAttuale->getProdotti(*tipo);   //ottengo i nomi dei prodotti di quel tipo

        for(const std::string* prod : prodottiTipo) {
            l->addItem(new QListWidgetItem( QString::fromStdString(*prod) ));       //aggiungo alla lista "tipo", tutti i prodotti di quel tipo
        }

        //creazione lista menu
        listaMenu.insert(l, *tipo);
        //creazione layout
        listaLayout.push_back(new QVBoxLayout);
        //aggiunta etichetta
        listaLayout.back()->addWidget(new QLabel(QString::fromStdString(*tipo)));
        //aggiunta lista menu al layout
        listaLayout.back()->addWidget(listaMenu.end().firstInfo());
    }

    //aggiunta al Layout principale
    for (QVBoxLayout* layout : listaLayout)
        mainLayout->addLayout(layout);

    for (myContainer<QListWidget*, std::string>::const_iterator it = listaMenu.begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        connect(lista, &QListWidget::itemSelectionChanged, this, &menuWindow::onItemSelectionChanged);
    }

    //creazione dei pulsanti di aggiunta e rimozione
    QPushButton *addButton = new QPushButton("Aggiungi", this);
    QPushButton *removeButton = new QPushButton("Rimuovi", this);

    //connessione pulsanti
    connect(addButton, &QPushButton::clicked, this, &menuWindow::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &menuWindow::onRemoveButtonClicked);

    //layout pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    //aggiunta al layout principale
    mainLayout->addLayout(buttonLayout);

    //impostazione del layout
    setLayout(mainLayout);
}

void menuWindow::onAddButtonClicked()
{
    comandaAggiungiProdottoDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted) {
        prodotto *p = dialog.getProdotto();
        std::string tipo;
        int res = 0;
        if(dynamic_cast<bevanda*>(p)) tipo = "bevanda";
        else if(dynamic_cast<pietanza_cucina*>(p)) tipo = "pietanza_cucina";
        else if(dynamic_cast<pietanza_griglie*>(p)) tipo = "pietanza_griglie";
        else throw std::runtime_error("onAddButton : tipo imprevisto");

        std::string nuovoProdotto = p->getNome();
        res = menuAttuale->aggiungiProdotto(nuovoProdotto, tipo);

        if (!res) {
            //salviamo
            menuAttuale->save();

            //aggiungiamo l'elemento alla lista corretta
            for (myContainer<QListWidget*, std::string>::const_iterator it = listaMenu.begin(); !it.isPastTheEnd(); ++it) {
                QListWidget* lista = it.firstInfo();
                std::string tp = it.secondInfo();
                if(tp == tipo)                                              //se è la lista del tipo corretto
                    lista->addItem(QString::fromStdString(nuovoProdotto));  //aggiungiamo il prodotto alla lista corretta
            }
        } else if(res == 1) {
            QMessageBox::critical(this, "Attenzione", (QString::fromStdString(tipo) + " " + QString::fromStdString(nuovoProdotto) + " non presente nel file dei prodotti."), QMessageBox::Ok);
        } else if(res == 2) {
            QMessageBox::critical(this, "Attenzione", (QString::fromStdString(tipo) + " " + QString::fromStdString(nuovoProdotto) + " già presente nel menu."), QMessageBox::Ok);
        }
    }
}

void menuWindow::onRemoveButtonClicked()
{
    QListWidget* selectedList = nullptr;    // La lista selezionata

    // Determina quale lista ha il focus
    for (myContainer<QListWidget*, std::string>::const_iterator it = listaMenu.begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        QList<QListWidgetItem*> selectedItems = lista->selectedItems();
        if (!selectedItems.isEmpty()) {
            selectedList = lista;
            break;
        }
    }

    // Rimuovi l'elemento selezionato se presente
    if (selectedList) {
        QList<QListWidgetItem*> selectedItems = selectedList->selectedItems();
        for (QListWidgetItem* selectedItem : selectedItems) {
            // Rimuovi l'elemento dal menuAttuale
            std::string selectedItemText = selectedItem->text().toStdString();
            menuAttuale->rimuoviProdotto(selectedItemText);
            menuAttuale->save();
            //romuovo dalla QListWidget
            delete selectedItem;
        }
    }
}

void menuWindow::onItemSelectionChanged()
{
    QListWidget* senderListWidget = qobject_cast<QListWidget*>(sender());

    //rimozione focus altre liste
    for (myContainer<QListWidget*, std::string>::const_iterator it = listaMenu.begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        if (senderListWidget != lista)   //se non è quella col focus
            lista->clearSelection();
    }
}
