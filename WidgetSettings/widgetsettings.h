#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QWidget>
#include <QGroupBox>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <ModBus/include/ModBusUSB.h>
#include <Settings/settings.h>

#define ORGANIZATION_NAME "Garant"
#define ORGANIZATION_DOMAIN "www.leningrad.com"
#define APPLICATION_NAME "garant diesel-admiral"

namespace Ui {
class WidgetSettings;
}
class WidgetSettings : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSettings(QWidget *parent = 0);
    ~WidgetSettings();
private slots:
    void on_pushButtonAccept_clicked();
    void closeEvent(QCloseEvent *event);
private:
    Ui::WidgetSettings *ui;
    TConfigUSBPort *ConfigUSBPort;
};

#endif // WIDGETSETTINGS_H
