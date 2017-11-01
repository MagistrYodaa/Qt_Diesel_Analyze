#ifndef WIDGETARCHIVE_H
#define WIDGETARCHIVE_H

#include <QStackedWidget>

namespace Ui {
class WidgetArchive;
}

class WidgetArchive : public QStackedWidget
{
    Q_OBJECT

public:
    explicit WidgetArchive(QWidget *parent = 0);
    ~WidgetArchive();

private slots:
    void on_acceptButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::WidgetArchive *ui;
};

#endif // WIDGETARCHIVE_H
