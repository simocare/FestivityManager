#include "manageComandeWindow.h"

manageComandeWindow::manageComandeWindow(QWidget *parent) : MainWindow(parent)
{
    setWindowTitle("Comanda");
    //creazione e impostazione del widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);

    QVBoxLayout *overviewLayout = new QVBoxLayout;  //per visualizzare la comanda (l'ultima)
    QGroupBox *groupBox1 = new QGroupBox("Dettagli Comanda");
    QFormLayout *form1 = new QFormLayout(groupBox1);
    groupBox1->setLayout(form1);

    overviewLayout->addWidget(groupBox1);

    QVBoxLayout *ordineLayout = new QVBoxLayout;    //visualizzare l'ordine
    QGroupBox *groupBox2 = new QGroupBox("Dettagli Ordine");
    QFormLayout *form2 = new QFormLayout(groupBox2);
    groupBox2->setLayout(form2);

    ordineLayout->addWidget(groupBox2);

    //aggiunti al mainLayout
    mainLayout->addLayout(overviewLayout);
    mainLayout->addLayout(ordineLayout);

    //ottengo i dati dell'ultima comanda
    std::vector<comanda*> comande = comanda::loadAll();
    //trovo l'ultima (num maggiore)
    int maxN=0, n=0;
    for(comanda* c : comande) {
        n = c->getNumero();
        if(n > maxN){
            maxN = n;
            com = c;
        }
    }
    QLabel *label1 = new QLabel(QString::number(com->getNumero()));
    QLabel *label2 = new QLabel(QString::fromStdString(com->getCameriere()->getUsername()));
    QLabel *label3 = new QLabel(QString::fromStdString(com->getDistributore()->getUsername()));
    QLabel *label4 = new QLabel(com->isAsporto() ? "Si" : "No");

    form1->addRow("NUM:", label1);
    form1->addRow("Cameriere:", label2);
    form1->addRow("Distributore:", label3);
    form1->addRow("Asporto:", label4);

    QPushButton *newComandaButton = new QPushButton("Nuova Comanda", this);

    overviewLayout->addWidget(newComandaButton);

    //connessione pulsante
    connect(newComandaButton, &QPushButton::clicked, this, &manageComandeWindow::onNewComandaButtonClicked);

    //PARTE DESTRA

    //titoli
    QHBoxLayout *titoliLayout = new QHBoxLayout;
    titoliLayout->addWidget(new QLabel("Prodotto"));
    titoliLayout->addWidget(new QLabel("numero occorrenze"));
    titoliLayout->addWidget(new QLabel("Prezzo Porzione"));

    form2->addRow("", titoliLayout);

    //lista
    ordineUI = new QListWidget;
    //il suo layout
    listaLayout = new QVBoxLayout;
    listaLayout->addWidget(ordineUI);

    std::vector<prodotto*> prodotti = com->getProdotti();
    //entro solo se ci sono prodotti da inserire
    if(prodotti[0]){
        for(prodotto *p : prodotti) {
            QListWidgetItem *item = new QListWidgetItem(ordineUI);

            QWidget *itemWidget = new QWidget;

            ordineUI->setItemWidget(item, itemWidget);

            QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

            QLabel *label1 = new QLabel(QString::fromStdString(p->getNome()));
            QLabel *label2 = new QLabel(QString::number(com->getNumeroOccorrenzeProdotto(p)));
            QLabel *label3 = new QLabel(QString::number(p->getPrezzoPorzione()) + " €");

            //imposto allineamento a destra
            label2->setAlignment(Qt::AlignLeft);
            label3->setAlignment(Qt::AlignLeft);

            itemLayout->addWidget(label1);
            itemLayout->addWidget(label2);
            itemLayout->addWidget(label3);

            itemWidget->setLayout(itemLayout);
            item->setSizeHint(itemWidget->sizeHint());

            ordineUI->addItem(item);
            ordineUI->setItemWidget(item, itemWidget);
        }
    }
    form2->addRow("", listaLayout);

    //TASTI AGGIUNGI E RIMUOVI
    //creazione dei pulsanti di aggiunta e rimozione
    QPushButton *addButton = new QPushButton("Aggiungi", this);
    QPushButton *removeButton = new QPushButton("Rimuovi", this);

    //connessione pulsanti
    connect(addButton, &QPushButton::clicked, this, &manageComandeWindow::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &manageComandeWindow::onRemoveButtonClicked);

    //layout pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    listaLayout->addLayout(buttonLayout);

    //totale
    QLabel *totLabel = new QLabel("Totale: " + QString::number(com->calcolaTotale()) + " €");
    totLabel->setAlignment(Qt::AlignRight);
    listaLayout->addWidget(totLabel);
}

//per fare il refresh rifaccio tutto quello fatto nel costruttore
void manageComandeWindow::refresh() {
    setWindowTitle("Comanda");
    //creazione e impostazione del widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);

    QVBoxLayout *overviewLayout = new QVBoxLayout;  //per visualizzare la comanda (l'ultima)
    QGroupBox *groupBox1 = new QGroupBox("Dettagli Comanda");
    QFormLayout *form1 = new QFormLayout(groupBox1);
    groupBox1->setLayout(form1);

    overviewLayout->addWidget(groupBox1);

    QVBoxLayout *ordineLayout = new QVBoxLayout;    //visualizzare l'ordine
    QGroupBox *groupBox2 = new QGroupBox("Dettagli Ordine");
    QFormLayout *form2 = new QFormLayout(groupBox2);
    groupBox2->setLayout(form2);

    ordineLayout->addWidget(groupBox2);

    //aggiunti al mainLayout
    mainLayout->addLayout(overviewLayout);
    mainLayout->addLayout(ordineLayout);

    //ottengo i dati dell'ultima comanda
    std::vector<comanda*> comande = comanda::loadAll();
    //trovo l'ultima (num maggiore)
    int maxN=0, n=0;
    for(comanda* c : comande) {
        n = c->getNumero();
        if(n > maxN){
            maxN = n;
            com = c;
        }
    }
    QLabel *label1 = new QLabel(QString::number(com->getNumero()));
    QLabel *label2 = new QLabel(QString::fromStdString(com->getCameriere()->getUsername()));
    QLabel *label3 = new QLabel(QString::fromStdString(com->getDistributore()->getUsername()));
    QLabel *label4 = new QLabel(com->isAsporto() ? "Si" : "No");

    form1->addRow("NUM:", label1);
    form1->addRow("Cameriere:", label2);
    form1->addRow("Distributore:", label3);
    form1->addRow("Asporto:", label4);

    QPushButton *newComandaButton = new QPushButton("Nuova Comanda", this);

    overviewLayout->addWidget(newComandaButton);

    //connessione pulsante
    connect(newComandaButton, &QPushButton::clicked, this, &manageComandeWindow::onNewComandaButtonClicked);

    //PARTE DESTRA

    //titoli
    QHBoxLayout *titoliLayout = new QHBoxLayout;
    titoliLayout->addWidget(new QLabel("Prodotto"));
    titoliLayout->addWidget(new QLabel("numero occorrenze"));
    titoliLayout->addWidget(new QLabel("Prezzo Porzione"));

    form2->addRow("", titoliLayout);

    //lista
    ordineUI = new QListWidget;
    //il suo layout
    listaLayout = new QVBoxLayout;
    listaLayout->addWidget(ordineUI);

    std::vector<prodotto*> prodotti = com->getProdotti();
    //entro solo se ci sono prodotti da inserire
    if(prodotti[0]){
        for(prodotto *p : prodotti) {
            QListWidgetItem *item = new QListWidgetItem(ordineUI);

            QWidget *itemWidget = new QWidget;

            ordineUI->setItemWidget(item, itemWidget);

            QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

            QLabel *label1 = new QLabel(QString::fromStdString(p->getNome()));
            QLabel *label2 = new QLabel(QString::number(com->getNumeroOccorrenzeProdotto(p)));
            QLabel *label3 = new QLabel(QString::number(p->getPrezzoPorzione()) + " €");

            //imposto allineamento a destra
            label2->setAlignment(Qt::AlignLeft);
            label3->setAlignment(Qt::AlignLeft);

            itemLayout->addWidget(label1);
            itemLayout->addWidget(label2);
            itemLayout->addWidget(label3);

            itemWidget->setLayout(itemLayout);
            item->setSizeHint(itemWidget->sizeHint());

            ordineUI->addItem(item);
            ordineUI->setItemWidget(item, itemWidget);
        }
    }
    form2->addRow("", listaLayout);

    //TASTI AGGIUNGI E RIMUOVI
    //creazione dei pulsanti di aggiunta e rimozione
    QPushButton *addButton = new QPushButton("Aggiungi", this);
    QPushButton *removeButton = new QPushButton("Rimuovi", this);

    //connessione pulsanti
    connect(addButton, &QPushButton::clicked, this, &manageComandeWindow::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &manageComandeWindow::onRemoveButtonClicked);

    //layout pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    listaLayout->addLayout(buttonLayout);

    //totale
    QLabel *totLabel = new QLabel("Totale: " + QString::number(com->calcolaTotale()) + " €");
    totLabel->setAlignment(Qt::AlignRight);
    listaLayout->addWidget(totLabel);
}

void manageComandeWindow::onAddButtonClicked() {
    comandaAggiungiProdottoDialog cdialog(this);
    if(cdialog.exec() == QDialog::Accepted) {
        prodotto *p = cdialog.getProdotto();

        com->aggiungiProdotto(p);
        com->save();

        refresh();

    } else QMessageBox::information(this, "Operazione annullata", "L'operazione è stata annullata. L'ordine è stato modificato.");
}

void manageComandeWindow::onRemoveButtonClicked() {
    QList<QListWidgetItem*> selectedItems = ordineUI->selectedItems();
    for (QListWidgetItem* selectedItem : selectedItems) {

        QWidget *itemWidget = ordineUI->itemWidget(selectedItem);
        if (itemWidget) {
            // Otteniamo il layout del widget
            QHBoxLayout *itemLayout = qobject_cast<QHBoxLayout*>(itemWidget->layout());
            if (itemLayout) {

                // Otteniamo il primo elemento del layout (il nome del prodotto)
                QLabel *label1 = qobject_cast<QLabel*>(itemLayout->itemAt(0)->widget());
                if (label1) {
                    //LEGGIAMO IL PRODOTTO DA MEMORIA
                    //proviamo in tutti i tipi
                    prodotto *target;
                    std::string nomeProd  = label1->text().toStdString();
                    bevanda *b = bevanda::load(nomeProd);
                    pietanza_cucina *pc = pietanza_cucina::load(nomeProd);
                    pietanza_griglie *pg = pietanza_griglie::load(nomeProd);

                    if(b) target = b;
                    else if(pc) target = pc;
                    else if(pg) target = pg;
                    else {
                        qDebug() << "errore, non trovato";
                        return;
                    }

                    std::cout << target->getNome() << std::endl;
                    com->rimuoviProdotto(target);
                    com->save();

                    refresh();
                }
            }
        }
    }
}

void manageComandeWindow::onNewComandaButtonClicked() {
    nuovaComandaDialog cdialog(this);
    if(cdialog.exec() == QDialog::Accepted) {

        //determino numero comanda
        std::vector<comanda*> comande = comanda::loadAll();
        auto s = comande.size();
        int siz = static_cast<int>(s);
        user *cam = cdialog.getCameriere();
        user *dis = cdialog.getDistributore();
        bool as = cdialog.isAsporto();

        comanda *x = new comanda(siz +1, cam, dis, as);

        x->save();
        qDebug() <<"arrivo";

        refresh();
    }
}
