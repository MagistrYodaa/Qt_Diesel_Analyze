#include "widgetvmtsetup.h"
#include "ui_widgetvmtsetup.h"

WidgetVMTSetup::WidgetVMTSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVMTSetup)
{
    ui->setupUi(this);

    ui->plot->xAxis->setRange(-180, 180);
    ui->plot->yAxis->setRange(1, 1.5);
    ui->plot->yAxis->setLabel("Кг/см2");
    ui->plot->xAxis->setLabel("Угол поворота К.В.");

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);

    //соеднинения для зума 1 - х ось, 2 - у ось
    //connect(ui->plot->xAxis, &QCPAxis::rangeChanged, ui->plot->xAxis2, &QCPAxis::setRange);
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
    //соединение для изменения текста осей
    connect(ui->plot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),
            this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
}

void WidgetVMTSetup::on_zoomOut_clicked()
{
    ui->plot->xAxis->scaleRange(1.15, ui->plot->xAxis->range().center());
    ui->plot->replot();
}

void WidgetVMTSetup::on_zoomIn_clicked()
{
    ui->plot->xAxis->scaleRange(.85, ui->plot->xAxis->range().center());
    ui->plot->replot();
}

void WidgetVMTSetup::on_meteringButton_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
    ui->labelMain->clear();

    QVector <int> usedChannels;
    QVector <int> indicesVector;
    QString answer;

    usedChannels.push_back(1);

    if(readFromFile(mapContainer, usedChannels, answer)){

        getIndicesVector(mapContainer["Channel_DUP"], indicesVector);

        if(!indicesVector.empty()){
            auto VMT = getVMTAngle(indicesVector, mapContainer["Channel_1"]);
            ui->labelMain->setText(answer + "  " + QString::number(VMT));
            getVMTDataVector(VMT, indicesVector, mapContainer["Channel_1"], vmtDataVector);
            saveVMT(VMT);
        }

        ui->plot->addGraph();
        ui->plot->graph()->setData(getAnglesVector(), vmtDataVector);
        ui->plot->yAxis->setRange(*std::min_element(vmtDataVector.begin(), vmtDataVector.end()), 1.5);
        ui->plot->replot();

        mapContainer.clear();
        usedChannels.clear();
        vmtDataVector.clear();
    }else{
        ui->labelMain->setText(answer);
    }

//    usedChannels.push_back(DieselType::getInstance().getWorkOrder().first()); // добавляем первый только первый цилиндр из порядка работы цилиндров(потому что другие нам не нужны)
//    if(readFromADC(mapContainer, usedChannels, answer)){

//        getIndicesVector(mapContainer["Channel_DUP"], indicesVector);

//        if(!indicesVector.empty()){
//            auto VMT = getVMTAngle(indicesVector, mapContainer["Channel_1"]);
//            ui->labelMain->setText(answer + "  " + QString::number(VMT));
//            getVMTDataVector(VMT, indicesVector, mapContainer["Channel_1"], vmtDataVector);
//            saveVMT(VMT);
//        }

//        ui->plot->addGraph();
//        ui->plot->graph()->setData(getAnglesVector(), vmtDataVector);
//        ui->plot->yAxis->setRange(*std::min_element(vmtDataVector.begin(), vmtDataVector.end()), 1.5);
//        ui->plot->replot();

//        mapContainer.clear();
//        usedChannels.clear();
//        vmtDataVector.clear();
//    }else{
//        ui->labelMain->setText(answer);
//    }
}

void WidgetVMTSetup::closeEvent(QCloseEvent *event)
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
        ui->plot->xAxis->setRange(-180, 180);
        ui->plot->yAxis->setRange(1, 1.5);
        ui->plot->clearGraphs();
        ui->plot->replot();
        ui->labelMain->clear();
        event->accept();
    }
}

WidgetVMTSetup::~WidgetVMTSetup()
{
    delete ui;
}
