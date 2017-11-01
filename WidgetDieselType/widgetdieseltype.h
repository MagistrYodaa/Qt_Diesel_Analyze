#ifndef WIDGETDIESELTYPE_H
#define WIDGETDIESELTYPE_H

#include <QWidget>
#include <QJsonObject>
#include <QSpinBox>
#include <QLayout>
#include <QList>
#include <QMessageBox>
#include <algorithm>
#include <DieselType/dieseltype.h>
#include <dataio/dataio.h>


namespace Ui {
class WidgetDieselType;
}
class WidgetDieselType : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetDieselType(QWidget *parent = 0);
    ~WidgetDieselType();
private slots:
    void on_acceptButton_clicked();
    void showSpinBoxes(int count);
    void on_acceptButton2_clicked();
    void clearLayout(QLayout *layout);
    QList<QVariant> getWorkOrder();
    void closeEvent(QCloseEvent *event);

private:
    Ui::WidgetDieselType *ui;
    QGridLayout *layoutSpinBoxes;
    QVector <QSpinBox*> spinBoxes;
};

#endif // WIDGETDIESELTYPE_H
