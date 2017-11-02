#include "widgetselectdiesel.h"
#include "ui_widgetselectdiesel.h"

WidgetSelectDiesel::WidgetSelectDiesel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSelectDiesel)
{
    ui->setupUi(this);

    QStringList headers;
    headers << "Марка дизеля" << "Число цил-ров" << "Тактность" << "Конструкция"
            << "Угол заклинки в ряду" << "Порядок работы" << "Диаметр цил-ра" << "Ход поршня"
            << "Длина шатуна";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->resizeColumnsToContents();

    bool ok;
    diesels = getDieselsMap(ok);
    QString workOrder;
    int i = 0;
    for (auto itv = diesels.begin(); itv != diesels.end(); ++itv){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(itv->value("dieseltype").toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(itv->value("cylinderscount").toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(itv->value("tacticity").toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(itv->value("anglez").toString()));
        for (QString str : itv->value("workOrder").toStringList()) workOrder.append(str + QString(" "));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(workOrder));
        workOrder.clear();
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(itv->value("cylinderdiameter").toString()));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(itv->value("pistonstroke").toString()));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(itv->value("conrodlenght").toString()));
        i++;
    }
}

void WidgetSelectDiesel::on_acceptButton_clicked()
{
    auto indexes = ui->tableWidget->selectionModel()->selectedRows();

    if (indexes.empty()){
        QMessageBox::information(this, "Дизель-Адмирал", "Дизель не выбран");
    } else {
        int index = indexes.at(0).row();

        QVector<int> workOrder;

        QString input(ui->tableWidget->item(index, 5)->text());

        QStringList slist;
        slist = input.split(" ");
        for (int i = 0; i < slist.size() - 1; ++i){
            workOrder.push_back(slist.at(i).toInt());
        }

        DieselType::getInstance().setDieselMark(ui->tableWidget->item(index, 0)->text());
        DieselType::getInstance().setCylindersCount(ui->tableWidget->item(index, 1)->text().toInt());
        DieselType::getInstance().setTacticity(ui->tableWidget->item(index, 2)->text().toInt());
        DieselType::getInstance().setAngleWedge(ui->tableWidget->item(index, 4)->text().toInt());
        DieselType::getInstance().setCylindersDiameter(ui->tableWidget->item(index, 6)->text().toDouble());
        DieselType::getInstance().setPistonStroke(ui->tableWidget->item(index, 7)->text().toDouble());
        DieselType::getInstance().setConrodLenght(ui->tableWidget->item(index, 8)->text().toDouble());
        DieselType::getInstance().setWorkOrder(workOrder);

        saveDefaultDiesel();

        emit activeDiesel(ui->tableWidget->item(index, 0)->text());
        //emit dieseliIsSelected(DieselType::getInstance().getCylindersCount());

        this->close();
    }
}

void WidgetSelectDiesel::on_deleteButton_clicked()
{
    auto indexes = ui->tableWidget->selectionModel()->selectedRows();

    int index = indexes.at(0).row();

    deleteDiesel(ui->tableWidget->item(index, 0)->text());

    ui->tableWidget->removeRow(index);
}

void WidgetSelectDiesel::updateTable()
{
    bool ok;
    diesels = getDieselsMap(ok);
    if (!ok){
        diesels.clear();
        QMessageBox::information(this, "Дизель-Адмирал", "Ошибка при работе с файлами");
    } else {
        QVector <QVariantMap> currentDiesels;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i){
            QVariantMap diesel;
            diesel.insert("dieseltype", ui->tableWidget->item(i, 0)->text());
            diesel.insert("cylinderscount", ui->tableWidget->item(i, 1)->text().toDouble());
            diesel.insert("tacticity", ui->tableWidget->item(i, 2)->text().toDouble());
            diesel.insert("anglez", ui->tableWidget->item(i, 4)->text().toDouble());
            auto list = QStringList(ui->tableWidget->item(i, 5)->text().split(" "));
            list.pop_back();
            diesel.insert("workOrder", list);
            diesel.insert("cylinderdiameter", ui->tableWidget->item(i, 6)->text().toDouble());
            diesel.insert("pistonstroke", ui->tableWidget->item(i, 7)->text().toDouble());
            diesel.insert("conrodlenght", ui->tableWidget->item(i, 8)->text().toDouble());
            currentDiesels.push_back(diesel);
        }
        for (auto itv = currentDiesels.begin();itv != currentDiesels.end(); itv++) {
            diesels.erase(std::remove(diesels.begin(), diesels.end(), *itv), diesels.end());
        }
        QString workOrder;
        int i = 0;
        for (auto itv = diesels.begin(); itv != diesels.end(); ++itv){
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(itv->value("dieseltype").toString()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(itv->value("cylinderscount").toString()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(itv->value("tacticity").toString()));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(itv->value("anglez").toString()));
            for (QString str : itv->value("workOrder").toStringList()) workOrder.append(str + QString(" "));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(workOrder));
            workOrder.clear();
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(itv->value("cylinderdiameter").toString()));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(itv->value("pistonstroke").toString()));
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(itv->value("conrodlenght").toString()));
            i++;
        }
    }
}

void WidgetSelectDiesel::closeEvent(QCloseEvent *event)
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

WidgetSelectDiesel::~WidgetSelectDiesel()
{
    delete ui;
}
