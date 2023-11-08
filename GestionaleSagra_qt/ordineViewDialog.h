#ifndef ORDINEVIEWDIALOG_H
#define ORDINEVIEWDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QLabel>
#include <vector>

#include "../Gestionale_sagra/comanda.h"

class ordineViewDialog : public QDialog
{
    Q_OBJECT

public:
    ordineViewDialog(comanda* com, QWidget *parent = nullptr);
};

#endif // ORDINEVIEWDIALOG_H
