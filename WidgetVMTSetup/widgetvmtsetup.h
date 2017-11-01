#ifndef WIDGETVMTSETUP_H
#define WIDGETVMTSETUP_H

#include <QWidget>
#include <QCustomPlot/qcustomplot.h>
#include <dataio/dataio.h>

namespace Ui {
class WidgetVMTSetup;
}
class WidgetVMTSetup : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetVMTSetup(QWidget *parent = 0);
    ~WidgetVMTSetup();
private slots:
    void on_zoomOut_clicked();
    void on_zoomIn_clicked();
    void on_meteringButton_clicked();
    void closeEvent(QCloseEvent *event);
private:
    Ui::WidgetVMTSetup *ui;
    QMap <QString, QVector<double>> mapContainer;
    QVector <double> vmtDataVector;
};

#endif // WIDGETVMTSETUP_H
