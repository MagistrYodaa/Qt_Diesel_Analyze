#include <WidgetArchive/widgetarchive.h>
#include "ui_widgetarchive.h"

WidgetArchive::WidgetArchive(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::WidgetArchive)
{
    ui->setupUi(this);
}

void WidgetArchive::on_acceptButton_clicked()
{
    ui->page->hide();
    ui->page_2->show();
}

void WidgetArchive::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox(
                QMessageBox::Question,
                tr("Дизель адмирал"),
                tr("Вы уверены?\n"),
                QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, tr("Да"));
    msgBox.setButtonText(QMessageBox::No, tr("Нет"));
    if (msgBox.exec() != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

WidgetArchive::~WidgetArchive()
{
    delete ui;
}
