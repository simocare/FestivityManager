#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Gestionale sagra");

    //ottengo le dimensioni dello schermo primario
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    if (primaryScreen) {
        QRect availableGeometry = primaryScreen->availableGeometry();

        //imposto le dimensioni della finestra
        setGeometry(availableGeometry);
    }
}

MainWindow::~MainWindow()
{
}
