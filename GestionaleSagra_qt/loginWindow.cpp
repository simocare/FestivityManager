#include "loginWindow.h"

loginWindow::loginWindow(QWidget *parent) : QDialog(parent)
{
    usrName="";

    setWindowTitle("Login");
    this->resize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Username");
    layout->addWidget(usernameLineEdit);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password); //nasconde il testo della password
    layout->addWidget(passwordLineEdit);

    QPushButton *loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    // Connessione del pulsante di login alla funzione di gestione del login
    connect(loginButton, &QPushButton::clicked, this, &loginWindow::accept);
}

void loginWindow::login()
{
    std::string username = usernameLineEdit->text().toStdString();
    std::string password = passwordLineEdit->text().toStdString();

    //LOAD DEGLI UTENTI
    std::vector<user*> utenti = user::loadAll();

    for(user* u : utenti){
        if(u->getUsername() == username) {
            if(u->getPassword() == password){

                usrName = username;
                return;
            }
            else
                QMessageBox::warning(this, "Login", "Password non valida. Riprova.");
        }
    }
    QMessageBox::warning(this, "Login", "Username non trovato. Riprova.");
}

void loginWindow::accept() {
    login();
    QDialog::accept();
}

std::string loginWindow::getRes() { return usrName; }
