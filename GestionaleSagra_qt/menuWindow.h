#ifndef MENUWINDOW_H
#define MENUWINDOW_H

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

#include "../Gestionale_sagra/menu.h"
#include "../Gestionale_sagra/jsonFileManager.h"

#include "../Gestionale_sagra/myContainer.h"
#include "manageComandeWindow.h"

class menuWindow : public QDialog
{
    Q_OBJECT

private:
    myContainer<QListWidget*, std::string> listaMenu; //firstInfo: la lista, secondInfo il tipo
    std::vector<QVBoxLayout*> listaLayout;
    std::vector<std::string*> tipi;

    menu* menuAttuale;

private slots:
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    // serve a fare in modo che venga selezionato un solo elemento tra tutte le categorie
    void onItemSelectionChanged();

public:
    menuWindow(QWidget *parent = nullptr);
};

#endif // MENUWINDOW_H
