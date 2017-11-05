#include "widgetsettings.h"
#include "ui_widgetsettings.h"

WidgetSettings::WidgetSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSettings)
{
    ui->setupUi(this);

    QRegExp pid("[1-9]\\d{0,3}");
    QValidator *validatorPID = new QRegExpValidator(pid, this);

    ui->lineEditPID->setValidator(validatorPID);
    ui->lineEditVID->setValidator(validatorPID);

    ui->spinBoxCount->setMaximum(MAX_COUNT_ADC);

    TConfigUSBPort ConfigUSBPort;
    Settings settings;

    settings.getUsbSettings(ConfigUSBPort);

    ui->lineEditPID->setText(QString("%1").arg(ConfigUSBPort.pid, 0 ,16).toUpper());
    ui->lineEditVID->setText(QString("%1").arg(ConfigUSBPort.vid, 0 ,16).toUpper());
    ui->spinBoxCount->setValue(ConfigUSBPort.adc_count);
    ui->spinBoxFreq->setValue(ConfigUSBPort.adc_freq);
    ui->spinBoxTimeout->setValue(ConfigUSBPort.timeOut);
    ui->spinBoxTreshold->setValue(settings.getTreshold());
    ui->spinBoxDUP->setValue(settings.getDupChannel());
}

void WidgetSettings::on_pushButtonAccept_clicked()
{
    Settings settings;
    bool ok;

    auto PID = QString("0x" + ui->lineEditPID->text()).toInt(&ok, 16);
    auto VID = QString("0x" + ui->lineEditVID->text()).toInt(&ok, 16);

    settings.setPID(PID);
    settings.setVID(VID);
    settings.setTimeOut(ui->spinBoxTimeout->value());
    settings.setFreq(ui->spinBoxFreq->value());
    settings.setCount(ui->spinBoxCount->value());
    settings.setTreshold(ui->spinBoxTreshold->value());
    settings.setDupChannel(ui->spinBoxDUP->value());
    settings.sync();

    QMessageBox msgBox(
                QMessageBox::Question,
                tr("Дизель адмирал"),
                tr("Настройки успешно сохранены\n"),
                QMessageBox::Ok);

    msgBox.setButtonText(QMessageBox::Ok, tr("Ок"));
    msgBox.exec();
}

void WidgetSettings::closeEvent(QCloseEvent *event)
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

WidgetSettings::~WidgetSettings()
{
    delete ui;
}
