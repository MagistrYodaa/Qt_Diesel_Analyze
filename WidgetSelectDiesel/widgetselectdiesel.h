#ifndef WIDGETSELECTDIESEL_H
#define WIDGETSELECTDIESEL_H

#include <QWidget>
#include <QGridLayout>
#include <QCloseEvent>
#include <QPushButton>
#include <DieselType/dieseltype.h>
#include <dataio/dataio.h>

namespace Ui {
class WidgetSelectDiesel;
}
class WidgetSelectDiesel : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSelectDiesel(QWidget *parent = 0);
    ~WidgetSelectDiesel();
    void updateTable();
signals:
    void activeDiesel(QString string);
    void dieseliIsSelected(int cylindersCount);
private slots:
    void on_acceptButton_clicked();
    void on_deleteButton_clicked();
    void closeEvent(QCloseEvent *event);
private:
    Ui::WidgetSelectDiesel *ui;
    QVector <QVariantMap> diesels;
};

#endif // WIDGETSELECTDIESEL_H
