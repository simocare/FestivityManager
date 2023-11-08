#ifndef MODIFICAUSERDIALOG_H
#define MODIFICAUSERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>

#include "../Gestionale_sagra/user.h"

#include "../Gestionale_sagra/pathManager.h"

class modificaUserDialog : public QDialog
{
    Q_OBJECT

public:
    modificaUserDialog(user *existingUser, QWidget *parent = nullptr);
    QString getRuolo() const;

private:
    QLabel *usernameLabel;
    QComboBox *ruoloComboBox;

    user *usr;

private slots:
    virtual void accept() override;
    void applyChanges();
};

#endif // MODIFICAUSERDIALOG_H
