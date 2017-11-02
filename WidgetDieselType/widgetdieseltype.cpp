#include "widgetdieseltype.h"
#include "ui_widgetdieseltype.h"

WidgetDieselType::WidgetDieselType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDieselType)
{
    ui->setupUi(this);

    layoutSpinBoxes = new QGridLayout(this);
    ui->groupBoxCylinders->setLayout(layoutSpinBoxes);
    QIntValidator *valid = new QIntValidator(0, 1000, this);
    ui->lineEditAngleZ->setValidator(valid);
    ui->lineEditDiameter->setValidator(valid);
    ui->lineEditLenght->setValidator(valid);
    ui->lineEditStroke->setValidator(valid);
}

void WidgetDieselType::clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while((child = layout->takeAt(0)) != 0){
        if(child->layout() != 0) clearLayout(child->layout());
        else if(child->widget() != 0) delete child->widget();
    }
    spinBoxes.clear();
}

QList<QVariant> WidgetDieselType::getWorkOrder()
{
    QList<QVariant> workOrder;
    for (auto item : spinBoxes) {
        if(std::find(workOrder.begin(), workOrder.end(), item->value()) == workOrder.end()){
            workOrder.push_back(item->value());
        }else{break;}
    }
    return workOrder;
}

void WidgetDieselType::on_acceptButton_clicked()
{
    if(ui->spinBoxCylindersCount->value() == 0
            || ui->lineEditAngleZ->text().isEmpty()
            || ui->lineEditDiameter->text().isEmpty()
            || ui->lineEditDieselType->text().isEmpty()
            || ui->lineEditLenght->text().isEmpty()
            || ui->lineEditStroke->text().isEmpty()){
        QMessageBox::information(this, "Дизель-Адмирал", "Не все поля заполнены");
    }else{
        clearLayout(layoutSpinBoxes);
        showSpinBoxes(ui->spinBoxCylindersCount->value());
    }
}

void WidgetDieselType::showSpinBoxes(int count)
{
    spinBoxes.reserve(count);
    QLabel* Labels[count];
    int column = 0;
    for(int i = 0; i < count; i++){
        Labels[i] = new QLabel(this);
        Labels[i]->setText(QString::number(i + 1) + " цилиндр");
        Labels[i]->setMaximumSize(70, 25);
        Labels[i]->setMinimumSize(70, 25);
        spinBoxes.push_back(new QSpinBox(this));
        spinBoxes[i]->setMaximumSize(40, 25);
        spinBoxes[i]->setMinimumSize(40, 25);
        spinBoxes[i]->setMinimum(1);
        spinBoxes[i]->setMaximum(count);
        if(layoutSpinBoxes->count() % 10 == 0){
            column += 2;
        }
        layoutSpinBoxes->addWidget(Labels[i], i%5, column);
        layoutSpinBoxes->addWidget(spinBoxes[i], i%5, column + 1);
        Labels[i]->show();
        spinBoxes[i]->show();
    }
}

void WidgetDieselType::on_acceptButton2_clicked()
{
    QVariantMap newDiesel;
    auto workOrder = getWorkOrder();
    if(workOrder.size() != ui->spinBoxCylindersCount->value()){
        QMessageBox::information(this, "Дизель-Адмирал", "Ошибка в порядке работы цилиндров");
    }else{
        newDiesel.insert(newDiesel.begin(), "dieseltype", ui->lineEditDieselType->text());
        newDiesel.insert(newDiesel.begin() + 1, "cylinderscount", ui->spinBoxCylindersCount->value());
        newDiesel.insert(newDiesel.begin() + 2, "anglez", ui->lineEditAngleZ->text().toInt());
        newDiesel.insert(newDiesel.begin() + 3, "pistonstroke", ui->lineEditStroke->text().toInt());
        newDiesel.insert(newDiesel.begin() + 4, "conrodlenght", ui->lineEditLenght->text().toInt());
        newDiesel.insert(newDiesel.begin() + 5, "cylinderdiameter", ui->lineEditDiameter->text().toInt());
        if(ui->radioButtonTact2->isChecked()) newDiesel.insert(newDiesel.begin() + 6, "tacticity", 2);
        if(ui->radioButtonTact4->isChecked()) newDiesel.insert(newDiesel.begin() + 6, "tacticity", 4);
        newDiesel.insert(newDiesel.begin() + 7, "workOrder", workOrder);

        if(addNewDiesel(newDiesel)){
            QMessageBox::information(this, "Дизель-Адмирал", "Дизель добавлен");
            this->close();
        }
        else{
            QMessageBox::information(this, "Дизель-Адмирал", "Ошибка сохранения дизеля в файл");
        }
    }
}

void WidgetDieselType::closeEvent(QCloseEvent *event)
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
        ui->lineEditDieselType->clear();
        ui->lineEditAngleZ->clear();
        ui->lineEditDiameter->clear();
        ui->lineEditLenght->clear();
        ui->lineEditStroke->clear();
        ui->spinBoxCylindersCount->setValue(1);
        clearLayout(layoutSpinBoxes);
        event->accept();
    }
}

WidgetDieselType::~WidgetDieselType()
{
    delete ui;
}
