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
    void on_buttonMetering2_clicked();
    void on_buttonSettings_clicked();
    void on_buttonDiesel1_clicked();
    void on_buttonMetering1_clicked();
    void on_buttonInd1_clicked();
    void on_buttonDiesel2_clicked();
    void setActiveDiesel(QString string);
    void on_buttonInd2_clicked();

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
