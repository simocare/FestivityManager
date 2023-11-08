#ifndef COMANDEWINDOW_H
#define COMANDEWINDOW_H

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

#include "../Gestionale_sagra/comanda.h"
#include "ordineViewDialog.h"

class comandeWindow : public QDialog
{
    Q_OBJECT

private:
    QListWidget *comandeUI;

    std::vector<comanda*> comande;

protected slots:
    void onViewButtonClicked();

public:
    comandeWindow(std::string username="", QWidget *parent = nullptr); //il parametro username permette di visalizzare solo le comande relative a quell'utente
};

#endif // COMANDEWINDOW_H
