QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Gestionale_sagra/bevanda.cpp \
    ../Gestionale_sagra/comanda.cpp \
    ../Gestionale_sagra/jsonFileManager.cpp \
    ../Gestionale_sagra/menu.cpp \
    ../Gestionale_sagra/pathManager.cpp \
    ../Gestionale_sagra/pietanza_cucina.cpp \
    ../Gestionale_sagra/pietanza_griglie.cpp \
    ../Gestionale_sagra/prodotto.cpp \
    ../Gestionale_sagra/user.cpp \
    adminWindow.cpp \
    comandaAggiungiProdottoDialog.cpp \
    comandeWindow.cpp \
    loginWindow.cpp \
    main.cpp \
    mainWindow.cpp \
    manageComandeWindow.cpp \
    menuWindow.cpp \
    modificaBevandaDialog.cpp \
    modificaPietanzaCucinaDialog.cpp \
    modificaPietanzaGriglieDialog.cpp \
    modificaProdottoDialog.cpp \
    modificaUserDialog.cpp \
    nuovaBevandaDialog.cpp \
    nuovaComandaDialog.cpp \
    nuovaPietanzaCucinaDialog.cpp \
    nuovaPietanzaGriglieDialog.cpp \
    nuovoProdottoDialog.cpp \
    nuovoUserDialog.cpp \
    ordineViewDialog.cpp \
    personaleWindow.cpp \
    prodottiWindow.cpp

HEADERS += \
    ../Gestionale_sagra/bevanda.h \
    ../Gestionale_sagra/comanda.h \
    ../Gestionale_sagra/jsonFileManager.h \
    ../Gestionale_sagra/menu.h \
    ../Gestionale_sagra/pathManager.h \
    ../Gestionale_sagra/pietanza_cucina.h \
    ../Gestionale_sagra/pietanza_griglie.h \
    ../Gestionale_sagra/prodotto.h \
    ../Gestionale_sagra/user.h \
    adminWindow.h \
    comandaAggiungiProdottoDialog.h \
    comandeWindow.h \
    loginWindow.h \
    mainWindow.h \
    manageComandeWindow.h \
    menuWindow.h \
    modificaBevandaDialog.h \
    modificaPietanzaCucinaDialog.h \
    modificaPietanzaGriglieDialog.h \
    modificaProdottoDialog.h \
    modificaUserDialog.h \
    nuovaBevandaDialog.h \
    nuovaComandaDialog.h \
    nuovaPietanzaCucinaDialog.h \
    nuovaPietanzaGriglieDiealog.h \
    nuovoProdottoDialog.h \
    nuovoUserDialog.h \
    ordineViewDialog.h \
    personaleWindow.h \
    prodottiWindow.h

CONFIG += lrelease
CONFIG += embed_translations

LIBS += -ljsoncpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Gestionale_sagra/comande.json \
    ../Gestionale_sagra/menu.json \
    ../Gestionale_sagra/paths.json \
    ../Gestionale_sagra/prodotti.json \
    ../Gestionale_sagra/tavoli.json \
    ../Gestionale_sagra/users.json
