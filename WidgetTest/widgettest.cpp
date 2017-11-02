#include "widgettest.h"
#include "ui_widgettest.h"

WidgetTest::WidgetTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTest)
{
    ui->setupUi(this);

    ui->plot->xAxis->setRange(0, 500);
    ui->plot->yAxis->setRange(-5, 5);

    getCountVector(countVector);

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);

    //соеднинения для зума 1 - х ось, 2 - у ось
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
    //соединение для изменения текста осей
    connect(ui->plot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),
            this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
}

void WidgetTest::on_meteringButton_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
    ui->labelMain->clear();

    QVector <int> usedChannels;
    QString answer;

    usedChannels.push_back(1);  // просто так выбрал 1 канал НО НАДО ЧТОБЫ В НАСТРОЙКАХ СТОЯЛО КАКОЙ КАНАЛ МЫ ПРОВЕРЯЕМ В ЭТОМ РЕЖИМЕ
    if(readFromADC(mapContainer, usedChannels, answer)){

        ui->plot->addGraph();

        if(ui->radioButtonDDG->isChecked()){
            ui->plot->graph()->setData(countVector, mapContainer["Channel_1"]);

        }else{
            ui->plot->graph()->setData(countVector, mapContainer["Channel_DUP"]);
        }
        ui->plot->replot();

        mapContainer.clear();
        usedChannels.clear();
    }else{
        ui->labelMain->setText(answer);
    }
}

void WidgetTest::on_zoomOut_clicked()
{
    if(ui->plot->xAxis->range().upper < 100000){
        auto newRange = (ui->plot->xAxis->range().upper)*2;
        ui->plot->xAxis->setRangeUpper(newRange);
        ui->plot->replot();
    }
}

void WidgetTest::on_zoomIn_clicked()
{
    if(ui->plot->xAxis->range().upper > 500){
            auto newRange = (ui->plot->xAxis->range().upper)*0.5;
            ui->plot->xAxis->setRangeUpper(newRange);
            ui->plot->replot();
        }
}

void WidgetTest::closeEvent(QCloseEvent *event)
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
        ui->plot->xAxis->setRange(0, 500);
        ui->plot->yAxis->setRange(-5, 5);
        ui->plot->clearGraphs();
        ui->plot->replot();
        ui->labelMain->clear();
        event->accept();
    }
}

WidgetTest::~WidgetTest()
{
    delete ui;
}
