#include "comandeWindow.h"

comandeWindow::comandeWindow(std::string username, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Comande");
    this->resize(800, 600);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    comandeUI = new QListWidget;

    setLayout(mainLayout);

    //aggiungiamo i titoli
    QHBoxLayout *titoliLayout = new QHBoxLayout;
    titoliLayout->addWidget(new QLabel("Numero Itentificativo"));
    titoliLayout->addWidget(new QLabel("Cameriere"));
    titoliLayout->addWidget(new QLabel("Distributore"));
    titoliLayout->addWidget(new QLabel("Asporto"));
    mainLayout->addLayout(titoliLayout);

    comande = comanda::loadAll();

    //per ogni elemento della lista
    for(const comanda* c : comande) {
        //Nel caso voglia filtrare: faccio le seguenti operazione solo se l'utente è cameriere o distributore di ogni comanda c
        //se non viene passato uno username mostra tutto
        if(username=="" || (c->getCameriere()->getUsername() == username) || (c->getDistributore()->getUsername() == username)) {
            //QListWidget
            //Creo un nuovo Item
            QListWidgetItem *item = new QListWidgetItem(comandeUI);

            //Creo un widget per l'item
            QWidget *itemWidget = new QWidget;

            //Imposto il widget creato
            comandeUI->setItemWidget(item, itemWidget);

            //Creo un layout QHBox per questo widget
            QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

            //Aggiungo al layout le parti
            QLabel *label1 = new QLabel(QString::number(c->getNumero()));
            QLabel *label2 = new QLabel(QString::fromStdString(c->getCameriere()->getUsername()));
            QLabel *label3 = new QLabel(QString::fromStdString(c->getDistributore()->getUsername()));
            QLabel *label4 = new QLabel((c->isAsporto() == true) ? "Si" : "No");

            itemLayout->addWidget(label1);
            itemLayout->addWidget(label2);
            itemLayout->addWidget(label3);
            itemLayout->addWidget(label4);

            itemWidget->setLayout(itemLayout);
            item->setSizeHint(itemWidget->sizeHint());

            comandeUI->addItem(item);
            comandeUI->setItemWidget(item, itemWidget);
        }
    }
    mainLayout->addWidget(comandeUI);

    QPushButton *ordineButton = new QPushButton("Visualizza Ordine");
    mainLayout->addWidget(ordineButton);

    connect(ordineButton, &QPushButton::clicked, this, &comandeWindow::onViewButtonClicked);
}

void comandeWindow::onViewButtonClicked() {
    QList<QListWidgetItem*> selectedItems = comandeUI->selectedItems();
    for (QListWidgetItem* selectedItem : selectedItems) {

        QWidget *itemWidget = comandeUI->itemWidget(selectedItem);
        if (itemWidget) {
            // Otteniamo il layout del widget
            QHBoxLayout *itemLayout = qobject_cast<QHBoxLayout*>(itemWidget->layout());

            if (itemLayout) {
                // Otteniamo il primo elemento del layout (il numero della comanda)
                QLabel *label1 = qobject_cast<QLabel*>(itemLayout->itemAt(0)->widget());

                if (label1) {
                    comanda *c = comanda::load((label1->text()).toInt());

                    ordineViewDialog odialog(c, this);
                    odialog.exec();
                }
            }
        }
    }
}
