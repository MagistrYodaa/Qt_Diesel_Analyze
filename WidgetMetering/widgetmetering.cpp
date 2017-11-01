#include <WidgetMetering/widgetmetering.h>
#include "ui_widgetmetering.h"

WidgetMetering::WidgetMetering(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMetering)
{
    ui->setupUi(this);

    this->setWindowTitle("Измерение");
    ui->plot->setBackground(QColor(240, 240, 240));
    ui->plot->xAxis->setRange(-180, 180);

    layoutRadioButtons = new QGridLayout(this);
    ui->groupBoxCylinders->setLayout(layoutRadioButtons);

//    ui->plot->yAxis->setRange(1, 1.5);
//    ui->plot->yAxis->setLabel("Кг/см2");
//    ui->plot->xAxis->setLabel("Угол поворота К.В.");

//    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
//                                    QCP::iSelectLegend | QCP::iSelectPlottables);

//    //соединяем сигнал и слот для передвижение по графику мышкой
//    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
//    //соединяем сигнал и слот для зума колесиком мышки
//    connect(ui->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
//    //соеднинения для зума 1 - х ось, 2 - у ось
//    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
//    //соединение для изменения текста осей
//    connect(ui->plot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),
//            this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
}

void WidgetMetering::showRadioButtons(int count)
{
    radioButtons.reserve(count);
    int column = 0;
    for(int i = 0; i < count; i++){
        radioButtons.push_back(new QRadioButton(this));
        radioButtons[i]->setMaximumSize(80, 25);
        radioButtons[i]->setMinimumSize(70, 25);
        radioButtons[i]->setText(QString::number(i + 1) + " цилиндр");
        if(layoutRadioButtons->count() % 5 == 0){
            column += 1;
        }
        layoutRadioButtons->addWidget(radioButtons[i], i%5, column);
        radioButtons[i]->show();
    }
}

void WidgetMetering::clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while((child = layout->takeAt(0)) != 0){
        if(child->layout() != 0) clearLayout(child->layout());
        else if(child->widget() != 0) delete child->widget();
    }
    radioButtons.clear();
}

void WidgetMetering::on_pushButton_5_clicked()
{
    ui->plot->clearGraphs();
    ui->plot->replot();
    QVector <int> usedChannels;
    QString answer;

    foreach (auto item, radioButtons) {
        if(item->isChecked()){
            auto cylinder = radioButtons.indexOf(item) + 1;
            usedChannels.push_back(cylinder);
        }
    }

    readFromFile(mapContainer, usedChannels, answer);
    //readFromADC(mapContainer, usedChannels, answer);

    QVector <int> indicesVector;
    getIndicesVector(mapContainer["Channel_DUP"], indicesVector);
    if(!indicesVector.empty()){
        getChannelsDataMap(mapContainer, getVMTAngle(), indicesVector, usedChannels.first());
    }

    ui->plot->addGraph();
    ui->plot->graph()->setData(getAnglesVector(), mapContainer.first());
    ui->plot->yAxis->setRange(*std::min_element(mapContainer.first().begin(), mapContainer.first().end()), 1.5);
    ui->plot->replot();

    usedChannels.clear();
    mapContainer.clear();
}

void WidgetMetering::closeEvent(QCloseEvent *event)
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
        clearLayout(layoutRadioButtons);
        ui->labelInfo->clear();
        ui->labelInfo_2->clear();
        ui->plot->clearGraphs();
        ui->plot->replot();
        event->accept();
    }
}

WidgetMetering::~WidgetMetering()
{
    delete ui;
}
