#include "MainWindow/mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    QApplication a(argc, argv);
    MainWindow w;

    QString datadir("Data");
    if(!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    QString settingsDir("Settings");
    if(!QDir(settingsDir).exists()){
        QDir().mkdir(settingsDir);
    }

    w.show();
    return a.exec();
}
