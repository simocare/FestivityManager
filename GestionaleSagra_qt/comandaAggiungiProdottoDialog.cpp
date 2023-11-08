#include "comandaAggiungiProdottoDialog.h"

comandaAggiungiProdottoDialog::comandaAggiungiProdottoDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Aggiungi Prodotto");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    comboProd = new QComboBox(this);
    mainLayout->addWidget(comboProd);

    //LEGGIAMO I PRODOTTI DA MEMORIA
    std::vector<prodotto*> prodotti;
    std::vector<bevanda*> bev = bevanda::loadAll();
    std::vector<pietanza_cucina*> pietanzeC = pietanza_cucina::loadAll();
    std::vector<pietanza_griglie*> pietanzeG = pietanza_griglie::loadAll();
    for(prodotto *p : bev) {                                         //tutte le bevande
        prodotti.push_back(p);
    }
    for(prodotto *p : pietanzeC) {                                   //tutte le pietanze cucina
        prodotti.push_back(p);
    }
    for(prodotto *p : pietanzeG) {                                   //tutte le pietanze cucina
        prodotti.push_back(p);
    }

    //aggiungiamo un opzione per ogni prodotto
    for(prodotto *p : prodotti) {
        comboProd->addItem(QString::fromStdString(p->getNome()));
    }

    // Aggiungi i pulsanti Ok e Annulla
    QPushButton *okButton = new QPushButton("Ok", this);
    QPushButton *cancelButton = new QPushButton("Annulla", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    // Connessioni dei pulsanti
    connect(okButton, &QPushButton::clicked, this, &comandaAggiungiProdottoDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &comandaAggiungiProdottoDialog::reject);
}

prodotto* comandaAggiungiProdottoDialog::getProdotto() const {
    return prod;
}

void comandaAggiungiProdottoDialog::accept() {
    //LEGGIAMO IL PRODOTTO DA MEMORIA
    //proviamo in tutti i tipi
    prodotto *target;
    std::string nomeProd = comboProd->currentText().toStdString();
    bevanda *b = bevanda::load(nomeProd);
    pietanza_cucina *pc = pietanza_cucina::load(nomeProd);
    pietanza_griglie *pg = pietanza_griglie::load(nomeProd);

    if(b) {
        target = b;
    } else if(pc) {
        target = pc;
    } else if(pg) {
        target = pg;
    }
    else {
        qDebug() << "errore, non trovato";
        return;
    }

    prod = target;

    QDialog::accept();
}
