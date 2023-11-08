#include "prodottiWindow.h"

prodottiWindow::prodottiWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Prodotti catalogo");
    mainLayout = new QVBoxLayout;

    listeProdottiUI = new myContainer<QListWidget*, std::string>;

    tipi.push_back(new std::string("bevanda"));
    tipi.push_back(new std::string("pietanza_cucina"));
    tipi.push_back(new std::string("pietanza_griglie"));

    //POPOLAMENTO delle liste di prodotti da json
    listaBevande = bevanda::loadAll();
    listaPcucina = pietanza_cucina::loadAll();
    listaPgriglie = pietanza_griglie::loadAll();


    for(const std::string* tipo : tipi) {
        //Creo la QListWidget per ogni tipo
        QListWidget* l = new QListWidget(this);

        if(*tipo == "bevanda") {
            for(const bevanda* b : listaBevande) {
                l->addItem(new QListWidgetItem(QString::fromStdString( b->getNome() )));
            }

        } else if(*tipo == "pietanza_cucina") {
            for(const pietanza_cucina* pc : listaPcucina) {
                l->addItem(new QListWidgetItem(QString::fromStdString( pc->getNome() )));
            }

        } else if(*tipo == "pietanza_griglie") {
            for(const pietanza_griglie* pg : listaPgriglie) {
                l->addItem(new QListWidgetItem(QString::fromStdString( pg->getNome() )));
            }

        } else {
            qDebug() << "tipo " + QString::fromStdString(*tipo) + " non riconosciuto";
        }

        listeProdottiUI->insert(l, *tipo);
        //creazione layout
        listaLayout.push_back(new QVBoxLayout);
        //aggiunta etichetta
        listaLayout.back()->addWidget(new QLabel(QString::fromStdString(*tipo)));
        //aggiunta lista menu al layout
        listaLayout.back()->addWidget(listeProdottiUI->end().firstInfo());
    }

    //aggiunta al Layout principale
    for (QVBoxLayout* layout : listaLayout)
        mainLayout->addLayout(layout);

    for (myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        connect(lista, &QListWidget::itemSelectionChanged, this, &prodottiWindow::onItemSelectionChanged);
    }

    QPushButton *addButton = new QPushButton("Aggiungi", this);
    QPushButton *editButton = new QPushButton("Modifica", this);
    QPushButton *removeButton = new QPushButton("Rimuovi", this);

    //connessione pulsanti
    connect(addButton, &QPushButton::clicked, this, &prodottiWindow::onAddButtonClicked);
    connect(editButton, &QPushButton::clicked, this, &prodottiWindow::onEditButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &prodottiWindow::onRemoveButtonClicked);

    //layout pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(removeButton);

    //aggiunta al layout principale
    mainLayout->addLayout(buttonLayout);

    //impostazione del layout
    setLayout(mainLayout);
}

void prodottiWindow::onAddButtonClicked()
{
    //Mostra una finestra di dialogo per la scelta del tipo
    QStringList tipo;
    //aggiunta a QStringList "tipo" dei tipi esistenti
    for (unsigned int i=0; i < tipi.size(); ++i)
        tipo << QString::fromStdString(*tipi[i]);

    bool ok;
    QString selectedType = QInputDialog::getItem(this, "Seleziona il tipo", "Seleziona il tipo:", tipo, 0, false, &ok);

    if (ok) {
        if (selectedType == "bevanda") {
            nuovaBevandaDialog bdialog(this);
            if(bdialog.exec() == QDialog::Accepted) { //utente ha premuto "ok"

                // Otteniamo i dati dalla finestra di dialogo
                std::string nome = bdialog.getNome().toStdString();
                double quantita = bdialog.getQuantita();
                float prezzoPorzione = bdialog.getPrezzoPorzione();
                float volumeUnit = bdialog.getVolumeUnit();
                bool alcool = bdialog.haAlcool();
                bool caffeina = bdialog.haCaffeina();
                bool zero = bdialog.isZero();

                // Creiamo un oggetto bevanda con i dati ottenuti
                bevanda nuovaBevanda(nome, quantita, quantita, prezzoPorzione, volumeUnit, alcool, caffeina, zero);

                nuovaBevanda.save();

                //aggiunge nuovo elemento alla lista grafica
                for(myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
                    QListWidget* l = it.firstInfo();
                    std::string tp = it.secondInfo();
                    if(tp == "bevanda")                     //se è la lista del tipo corretto
                        l->addItem(bdialog.getNome());  //aggiungiamo il prodotto alla lista corretta
                }

            } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessun nuovo prodotto è stato aggiunto.");

        } else if (selectedType == "pietanza_cucina") {
            nuovaPietanzaCucinaDialog pcdialog(this);
            if(pcdialog.exec() == QDialog::Accepted) {

                // Ottenere i dati dalla finestra di dialogo
                std::string nome = pcdialog.getNome().toStdString();
                double quantita = pcdialog.getQuantita();
                float prezzoPorzione = pcdialog.getPrezzoPorzione();

                pietanza_cucina nuovaPcucina(nome, quantita, quantita, prezzoPorzione);

                nuovaPcucina.save();

                //aggiunge nuovo elemento alla lista grafica
                for(myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
                    QListWidget* l = it.firstInfo();
                    std::string tp = it.secondInfo();
                    if(tp == "pietanza_cucina")                     //se è la lista del tipo corretto
                        l->addItem(pcdialog.getNome());  //aggiungiamo il prodotto alla lista corretta
                }

            } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessun nuovo prodotto è stato aggiunto.");

        } else if (selectedType == "pietanza_griglie") {
            nuovaPietanzaGriglieDialog pgdialog(this);
            if(pgdialog.exec() == QDialog::Accepted) {

                // Ottenere i dati dalla finestra di dialogo
                std::string nome = pgdialog.getNome().toStdString();
                double quantita = pgdialog.getQuantita();
                float prezzoPorzione = pgdialog.getPrezzoPorzione();
                float peso = pgdialog.getPesoPorzione();

                pietanza_griglie nuovaPgriglie(nome, quantita, quantita, prezzoPorzione, peso);

                nuovaPgriglie.save();

                //aggiunge nuovo elemento alla lista grafica
                for(myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
                    QListWidget* l = it.firstInfo();
                    std::string tp = it.secondInfo();
                    if(tp == "pietanza_griglie")                     //se è la lista del tipo corretto
                        l->addItem(pgdialog.getNome());  //aggiungiamo il prodotto alla lista corretta
                }

            } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessun nuovo prodotto è stato aggiunto.");
        }
    }

}

void prodottiWindow::onEditButtonClicked() {
    QListWidget* selectedList = nullptr;    // La lista selezionata
    std::string tipo;

    // Determina quale lista ha il focus
    for (myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        tipo = it.secondInfo();
        QList<QListWidgetItem*> selectedItems = lista->selectedItems();
        if (!selectedItems.isEmpty()) {
            selectedList = lista;
            break;
        }
    }

    if (selectedList) {
        QList<QListWidgetItem*> selectedItems = selectedList->selectedItems();
        for (QListWidgetItem* selectedItem : selectedItems) {
            std::string selectedItemText = selectedItem->text().toStdString();

            prodotto *prod;

            if(tipo == "bevanda") {
                prod = bevanda::load(selectedItemText);

                modificaBevandaDialog bdialog (prod, this);
                if(bdialog.exec() == QDialog::Accepted) {

                    //rimuovo quello esistente
                    prodotto::remove(prod->getNome(), "bevanda");
                    //aggiungo quello nuovo, che ha le modifiche
                    prod->save();

                } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessuna modifica è stata applicata.");

            } else if (tipo == "pietanza_cucina") {
                prod = pietanza_cucina::load(selectedItemText);

                modificaPietanzaCucinaDialog pcdialog (prod, this);
                if(pcdialog.exec() == QDialog::Accepted) {

                    //rimuovo quello esistente
                    prodotto::remove(prod->getNome(), "pietanza_cucina");
                    //aggiungo quello nuovo, che ha le modifiche
                    prod->save();

                } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessuna modifica è stata applicata.");

            } else if (tipo == "pietanza_griglie") {
                prod = pietanza_griglie::load(selectedItemText);

                modificaPietanzaGriglieDialog pgdialog (prod, this);
                if(pgdialog.exec() == QDialog::Accepted) {

                    //rimuovo quello esistente
                    prodotto::remove(prod->getNome(), "pietanza_griglie");
                    //aggiungo quello nuovo, che ha le modifiche
                    prod->save();

                } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. Nessuna modifica è stata applicata.");

            } else
                qDebug() << "non rientra tra i tipi attualmente previsti";
        }
    }
}
void prodottiWindow::onRemoveButtonClicked()
{
    QListWidget* selectedList = nullptr;    // La lista selezionata
    std::string tipo;

    // Determina quale lista ha il focus
    for (myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        tipo = it.secondInfo();
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
            std::string selectedItemText = selectedItem->text().toStdString();
            prodotto::remove(selectedItemText, tipo);

            delete selectedItem;
        }
    }
}

void prodottiWindow::onItemSelectionChanged()
{
    QListWidget* senderListWidget = qobject_cast<QListWidget*>(sender());

    //rimozione focus altre liste
    for (myContainer<QListWidget*, std::string>::const_iterator it = listeProdottiUI->begin(); !it.isPastTheEnd(); ++it) {
        QListWidget* lista = it.firstInfo();
        if (senderListWidget != lista)   //se non è quella col focus
            lista->clearSelection();
    }
}
