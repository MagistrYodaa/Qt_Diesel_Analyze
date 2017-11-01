#ifndef WIDGETMETERING_H
#define WIDGETMETERING_H

#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include "DieselType/dieseltype.h"
#include "dataio/dataio.h"

namespace Ui {
class WidgetMetering;
}
class WidgetMetering : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMetering(QWidget *parent = 0);
    ~WidgetMetering();
    void showRadioButtons(int count);
private slots:
    void on_pushButton_5_clicked();
    void clearLayout(QLayout *layout);
    void closeEvent(QCloseEvent *event);
private:
    Ui::WidgetMetering *ui;
    QMap <QString, QVector<double>> mapContainer;
    QGridLayout *layoutRadioButtons;
    QVector <QRadioButton*> radioButtons;
};

#endif // WIDGETMETERING_H
