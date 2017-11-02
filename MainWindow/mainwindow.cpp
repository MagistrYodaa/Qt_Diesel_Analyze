#include "mainwindow.h"
#include "ui_mainwindow.h"

#define USB_DEBUG_LEVEL         0
#define WORK_INTERFACE          0x00
#define EP_IN_CONTROL           0x81
#define EP_OUT_CONTROL          0x02
#define EP_IN_DATA              0x83

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getDefaultDiesel();

    ui->labelDieselInfo->setText(DieselType::getInstance().getDieselMark());

    testWidget = new WidgetTest();
    settingsWidget = new WidgetSettings();
    dieselTypeWidget = new WidgetDieselType();
    VMTSetupWidget = new WidgetVMTSetup();
    meteringWidget = new WidgetMetering();
    selectDieselWidget = new WidgetSelectDiesel();
    archiveWidget = new WidgetArchive();

    connect(selectDieselWidget, &WidgetSelectDiesel::activeDiesel, this, &MainWindow::setActiveDiesel);
    connect(this, &MainWindow::updateTable, selectDieselWidget, &WidgetSelectDiesel::updateTable);
    //connect(selectDieselWidget, &WidgetSelectDiesel::dieseliIsSelected, meteringWidget, &WidgetMetering::showRadioButtons);

}

void MainWindow::on_buttonMetering2_clicked()
{
    testWidget->show();
}

void MainWindow::on_buttonSettings_clicked()
{
    settingsWidget->show();
}

void MainWindow::on_buttonDiesel1_clicked()
{
    dieselTypeWidget->show();
}

void MainWindow::on_buttonMetering1_clicked()
{
    VMTSetupWidget->show();
}

void MainWindow::on_buttonInd1_clicked()
{
    if(DieselType::getInstance().getWorkOrder().empty()){
        QMessageBox::information(this, "Дизель-Адмирал", "Дизель не выбран");
    }else{
        meteringWidget->showRadioButtons(DieselType::getInstance().getCylindersCount());
        meteringWidget->show();
    }
}

void MainWindow::on_buttonDiesel2_clicked()
{
    emit updateTable();
    selectDieselWidget->show();
}

void MainWindow::setActiveDiesel(QString string)
{
    ui->labelDieselInfo->setText(string);
}

void MainWindow::on_buttonInd2_clicked()
{
    archiveWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

