#include "ordineViewDialog.h"

ordineViewDialog::ordineViewDialog(comanda *com, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Ordine");
    this->resize(500, 250);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    //aggiungiamo i titoli
    QHBoxLayout *titoliLayout = new QHBoxLayout;
    titoliLayout->addWidget(new QLabel("Prodotto"));
    titoliLayout->addWidget(new QLabel("numero occorrenze"));
    titoliLayout->addWidget(new QLabel("Prezzo Porzione"));
    mainLayout->addLayout(titoliLayout);

    QListWidget *ordineUI = new QListWidget;

    std::vector<prodotto*> prodotti = com->getProdotti();

    for(prodotto* p : prodotti) {
        QListWidgetItem *item = new QListWidgetItem(ordineUI);

        QWidget *itemWidget = new QWidget;

        ordineUI->setItemWidget(item, itemWidget);

        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

        QLabel *label1 = new QLabel(QString::fromStdString(p->getNome()));
        QLabel *label2 = new QLabel(QString::number(com->getNumeroOccorrenzeProdotto(p)));
        QLabel *label3 = new QLabel(QString::number(p->getPrezzoPorzione()) + " €");

        //imposto allineamento a destra
        label2->setAlignment(Qt::AlignRight);
        label3->setAlignment(Qt::AlignRight);

        itemLayout->addWidget(label1);
        itemLayout->addWidget(label2);
        itemLayout->addWidget(label3);

        itemWidget->setLayout(itemLayout);
        item->setSizeHint(itemWidget->sizeHint());

        ordineUI->addItem(item);
        ordineUI->setItemWidget(item, itemWidget);
    }
    mainLayout->addWidget(ordineUI);

    QLabel *label4 = new QLabel("Totale: " + QString::number(com->calcolaTotale()) + " €");
    label4->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(label4);
}
