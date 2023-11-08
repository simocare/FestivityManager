#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "mainWindow.h"
#include "menuWindow.h"
#include "prodottiWindow.h"
#include "personaleWindow.h"
#include "comandeWindow.h"
#include "manageComandeWindow.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QSpacerItem>

#include <QFont>

class adminWindow : public MainWindow
{
private:
    QLabel* label1;
public:
    adminWindow(QWidget *parent = nullptr);
    virtual ~adminWindow() override;

    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onButton5Clicked();
    void onButton6Clicked();
};
#endif // ADMINWINDOW_H
