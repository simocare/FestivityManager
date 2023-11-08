#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QApplication>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "../Gestionale_sagra/user.h"

class loginWindow : public QDialog {
    Q_OBJECT

public:
    loginWindow(QWidget *parent = nullptr);
    void login();
    std::string getRes();

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;

    std::string usrName;    //risultato che verrà restituito

private slots:
    virtual void accept() override;

};

#endif // LOGINWINDOW_H
