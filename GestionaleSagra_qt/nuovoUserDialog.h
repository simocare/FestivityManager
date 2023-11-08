#ifndef NUOVOUSERDIALOG_H
#define NUOVOUSERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>

class nuovoUserDialog : public QDialog
{
    Q_OBJECT

public:
    nuovoUserDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getRuolo() const;

private:
    QLineEdit *usernameLineEdit;
    QComboBox *ruoloComboBox;

private slots:
    virtual void accept() override;
};

#endif // NUOVOUSERDIALOG_H
