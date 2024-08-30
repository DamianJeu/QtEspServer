#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

    QApplication::setApplicationName("EspServer");
    QApplication::setApplicationVersion("0.0.1");
    QApplication::setOrganizationName("Zamel");
    QApplication::setOrganizationDomain("zamel.com");

    MainWindow w;

    w.show();
    return a.exec();
}
