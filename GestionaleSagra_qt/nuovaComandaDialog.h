#ifndef NUOVACOMANDADIALOG_H
#define NUOVACOMANDADIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>

#include "../Gestionale_sagra/user.h"

class nuovaComandaDialog : public QDialog
{
    Q_OBJECT

public:
    nuovaComandaDialog(QWidget *parent = nullptr);
    user* getCameriere() const;
    user* getDistributore() const;
    bool isAsporto() const;

private:
    QComboBox *cameriereCB;
    QComboBox *distributoreCB;
    QComboBox *asportoCB;

    user *cameriere;
    user *distributore;
    bool asporto;

private slots:
    virtual void accept() override;
};

#endif // NUOVACOMANDADIALOG_H
