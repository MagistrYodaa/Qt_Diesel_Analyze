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

    DieselType::getInstance().loadDefaultDiesel();

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


    //connect(ui->buttonDieselType, &QPushButton::clicked, dieselTypeWidget, &WidgetDieselType::show);
    //connect(ui->buttonSelectDiesel, &QPushButton::clicked, selectDieselWidget, &WidgetSelectDiesel::show);
    //connect(ui->buttonVMTSetup, &QPushButton::clicked, VMTSetupWidget, &WidgetVMTSetup::show);
    //connect(ui->buttonTest, &QPushButton::clicked, testWidget, &WidgetTest::show);
    //connect(ui->buttonMetering, &QPushButton::clicked, meteringWidget, &WidgetMetering::show);
    //connect(ui->buttonArchive, &QPushButton::clicked, archiveWidget, &WidgetArchive::show);
    //connect(selectDieselWidget, &WidgetSelectDiesel::dieseliIsSelected, meteringWidget, &WidgetMetering::showRadioButtons);

}

void MainWindow::setActiveDiesel(QString string)
{
    ui->labelDieselInfo->setText(string);
}

void MainWindow::on_buttonDieselType_clicked()
{
    dieselTypeWidget->show();
}

void MainWindow::on_buttonSelectDiesel_clicked()
{
    emit updateTable();
    selectDieselWidget->show();
}

void MainWindow::on_buttonVMTSetup_clicked()
{
    VMTSetupWidget->show();
}

void MainWindow::on_buttonTest_clicked()
{
    testWidget->show();
}

void MainWindow::on_buttonMetering_clicked()
{
    if(DieselType::getInstance().getWorkOrder().empty()){
        QMessageBox::information(this, "Дизель-Адмирал", "Дизель не выбран");
    }else{
        meteringWidget->showRadioButtons(DieselType::getInstance().getCylindersCount());
        meteringWidget->show();
    }
}

void MainWindow::on_buttonArchive_clicked()
{
    archiveWidget->show();
}

void MainWindow::on_buttonSettings_clicked()
{
    settingsWidget->show();
}

MainWindow::~MainWindow()
{
    delete testWidget;
    delete settingsWidget;
    delete dieselTypeWidget;
    delete VMTSetupWidget;
    delete meteringWidget;
    delete selectDieselWidget;
    delete archiveWidget;
    delete ui;
}
