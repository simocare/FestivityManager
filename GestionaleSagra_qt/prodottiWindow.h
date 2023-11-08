#ifndef PRODOTTIWINDOW_H
#define PRODOTTIWINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>

#include <QString>
#include <QInputDialog>

#include <QLabel>
#include <vector>
#include <string>

#include <QDebug>

#include "../Gestionale_sagra/bevanda.h"
#include "../Gestionale_sagra/pietanza_cucina.h"
#include "../Gestionale_sagra/pietanza_griglie.h"

#include "../Gestionale_sagra/myContainer.h"

#include "nuovaBevandaDialog.h"
#include "nuovaPietanzaCucinaDialog.h"
#include "nuovaPietanzaGriglieDiealog.h"

#include "modificaBevandaDialog.h"
#include "modificaPietanzaCucinaDialog.h"
#include "modificaPietanzaGriglieDialog.h"

class prodottiWindow : public QDialog
{
    Q_OBJECT

private:
    myContainer<QListWidget*, std::string> *listeProdottiUI; //firstInfo: la lista, secondInfo il tipo
    std::vector<QVBoxLayout*> listaLayout;
    std::vector<std::string*> tipi;
    QVBoxLayout *mainLayout;

    //vector di puntatori a bevande
    std::vector<bevanda*> listaBevande;
    //vector di puntatori a pietanze cucina
    std::vector<pietanza_cucina*> listaPcucina;
    //vector di puntatori a pietanze griglie
    std::vector<pietanza_griglie*> listaPgriglie;

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked();
    void onRemoveButtonClicked();
    // serve a fare in modo che venga selezionato un solo elemento tra tutte le categorie
    void onItemSelectionChanged();

public:
    prodottiWindow(QWidget *parent = nullptr);
};

#endif // PRODOTTIWINDOW_H
