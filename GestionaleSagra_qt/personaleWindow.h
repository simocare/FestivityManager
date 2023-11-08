#ifndef PERSONALEWINDOW_H
#define PERSONALEWINDOW_H

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

#include "../Gestionale_sagra/user.h"
#include "nuovoUserDialog.h"
#include "modificaUserDialog.h"

class personaleWindow : public QDialog
{
    Q_OBJECT

private:
    QListWidget *personaleUI;

    //vector di puntatori a user
    std::vector<user*> personale;

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked();
    void onRemoveButtonClicked();

public:
    personaleWindow(QWidget *parent = nullptr);
};

#endif // PERSONALEWINDOW_H
