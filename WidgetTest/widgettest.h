#ifndef WIDGETTEST_H
#define WIDGETTEST_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLayout>
#include <QMap>
#include "QCustomPlot//qcustomplot.h"
#include "ModBus/include/ModBusUSB.h"
#include "dataio/dataio.h"
#include "Settings/settingsclass.h"

namespace Ui {
class WidgetTest;
}
class WidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetTest(QWidget *parent = 0);
    ~WidgetTest();
private slots:
    void on_meteringButton_clicked();
    void on_zoomOut_clicked();
    void on_zoomIn_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::WidgetTest *ui;
    QMap <QString, QVector<double>> mapContainer;
    QVector <double> countVector;
};

#endif // WIDGETTEST_H
