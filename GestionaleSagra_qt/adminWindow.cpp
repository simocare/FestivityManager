#include "adminWindow.h"

adminWindow::adminWindow(QWidget *parent) : MainWindow(parent)
{
    setWindowTitle("Amministratore");

    //creazione e impostazione del widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //creazione del layout principale
    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);

    //creazione del layout per i pulsanti
    QVBoxLayout *buttonsLayout = new QVBoxLayout;

    QGroupBox *groupBox = new QGroupBox();
    QFormLayout *form = new QFormLayout(groupBox);
    groupBox->setLayout(form);

    QSpacerItem *spacer1 = new QSpacerItem(500, 500);
    QSpacerItem *spacer2 = new QSpacerItem(500, 500);
    mainLayout->addSpacerItem(spacer1);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addSpacerItem(spacer2);

//    QSpacerItem *spacer3 = new QSpacerItem(400, 400);
//    buttonsLayout->addSpacerItem(spacer3);

    buttonsLayout->addWidget(groupBox);

    //QPushButton *button1 = new QPushButton("Pulsante 1", this);
    QPushButton *button1 = new QPushButton("Imposta menu del giorno", this);
    QPushButton *button2 = new QPushButton("Prodotti catalogo", this);
    QPushButton *button3 = new QPushButton("Gestione personale", this);
    QPushButton *button4 = new QPushButton("Overview Comande", this);

    // Impostazioni estetiche dei pulsanti
    button1->setFixedHeight(80);
    button2->setFixedHeight(80);
    button3->setFixedHeight(80);
    button4->setFixedHeight(80);

    QFont font;
    font.setPointSize(16);
    button1->setFont(font);
    button2->setFont(font);
    button3->setFont(font);
    button4->setFont(font);

    QSpacerItem *vertical1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vertical2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vertical3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vertical4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *vertical5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    form->addItem(vertical1);
    form->addRow(button1);
    form->addItem(vertical2);
    form->addRow(button2);
    form->addItem(vertical3);
    form->addRow(button3);
    form->addItem(vertical4);
    form->addRow(button4);
    form->addItem(vertical5);

    // Connessione degli slot ai pulsanti
    connect(button1, &QPushButton::clicked, this, &adminWindow::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &adminWindow::onButton2Clicked);
    connect(button3, &QPushButton::clicked, this, &adminWindow::onButton3Clicked);
    connect(button4, &QPushButton::clicked, this, &adminWindow::onButton4Clicked);
}

adminWindow::~adminWindow()
{
}

void adminWindow::onButton1Clicked()
{
    menuWindow mw;
    //exec perché deve è una modal dialog, quindi blocca le altre finestre, finché questa non viene chiusa
    mw.exec();
}

void adminWindow::onButton2Clicked()
{
    prodottiWindow pw;
    pw.exec();
}

void adminWindow::onButton3Clicked()
{
    personaleWindow pw;
    pw.exec();
}

void adminWindow::onButton4Clicked()
{
    comandeWindow cw;
    cw.exec();
}
