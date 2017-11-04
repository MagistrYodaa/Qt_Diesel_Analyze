#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include "ModBus/include/ModBusUSB.h"
#include "QCustomPlot/qcustomplot.h"
#include "WidgetTest/widgettest.h"
#include "WidgetSettings/widgetsettings.h"
#include "Settings/settings.h"
#include "WidgetDieselType/widgetdieseltype.h"
#include "WidgetVMTSetup/widgetvmtsetup.h"
#include "WidgetMetering/widgetmetering.h"
#include "WidgetSelectDiesel/widgetselectdiesel.h"
#include "WidgetArchive/widgetarchive.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void updateTable();
private slots:
    void setActiveDiesel(QString string);
    void on_buttonDieselType_clicked();
    void on_buttonSelectDiesel_clicked();
    void on_buttonVMTSetup_clicked();
    void on_buttonTest_clicked();
    void on_buttonMetering_clicked();
    void on_buttonArchive_clicked();
    void on_buttonSettings_clicked();

private:
    Ui::MainWindow *ui;
    WidgetTest *testWidget;
    WidgetSettings *settingsWidget;
    WidgetDieselType *dieselTypeWidget;
    WidgetVMTSetup *VMTSetupWidget;
    WidgetMetering *meteringWidget;
    WidgetSelectDiesel *selectDieselWidget;
    WidgetArchive *archiveWidget;
};

#endif // MAINWINDOW_H
