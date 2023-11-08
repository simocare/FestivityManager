#ifndef MANAGECOMANDEWINDOW_H
#define MANAGECOMANDEWINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>

#include <QString>

#include <QLabel>
#include <vector>
#include <string>

#include <QDebug>
#include <QFormLayout>
#include <QGroupBox>

#include "mainWindow.h"
#include "../Gestionale_sagra/comanda.h"
#include "../Gestionale_sagra/bevanda.h"
#include "../Gestionale_sagra/pietanza_cucina.h"
#include "../Gestionale_sagra/pietanza_griglie.h"
#include "comandaAggiungiProdottoDialog.h"
#include "nuovaComandaDialog.h"

class manageComandeWindow : public MainWindow
{
private:
    QListWidget *ordineUI;
    QVBoxLayout *listaLayout;
    comanda *com;

private slots:
    void refresh();
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    void onNewComandaButtonClicked();

public:
    manageComandeWindow(QWidget *parent = nullptr);
};

#endif // MANAGECOMANDEWINDOW_H
