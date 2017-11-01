#include <MainWindow/mainwindow.h>
#include <QApplication>
#include <Settings/settings.h>




int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QApplication a(argc, argv);
    MainWindow w;

    QString *datadir = new QString("Data");
    if(!QDir(*datadir).exists()){
        QDir().mkdir(*datadir);
    }
    QString *settingsDir = new QString("Settings");
    if(!QDir(*settingsDir).exists()){
        QDir().mkdir(*settingsDir);
    }
    delete datadir;
    delete settingsDir;

    QIcon icon("C:\\Users\\Ruslan\\YandexDisk\\Garant_v2\\release\\icon.png");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
