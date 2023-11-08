#include "adminWindow.h"
#include "manageComandeWindow.h"
#include "loginWindow.h"
#include "comandeWindow.h"

#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    adminWindow w;
    manageComandeWindow mw;

    loginWindow lw;
    if(lw.exec() == QDialog::Accepted){

        std::string res = lw.getRes();

        if(res == "admin") {
            w.show();

        } else if(res == "cassiere") {
            mw.show();

        } else {
            comandeWindow uw(res);
            uw.exec();
        }

    } else std::cerr << "Operazione annullata" << std::endl;

    return a.exec();
}
