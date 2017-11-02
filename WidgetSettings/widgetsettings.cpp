#include "widgetsettings.h"
#include "ui_widgetsettings.h"

#include <string>

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
    getUsbSettings(ConfigUSBPort);

    ui->lineEditPID->setText(QString("%1").arg(ConfigUSBPort.pid, 0 ,16).toUpper());
    ui->lineEditVID->setText(QString("%1").arg(ConfigUSBPort.vid, 0 ,16).toUpper());
    ui->spinBoxCount->setValue(ConfigUSBPort.adc_count);
    ui->spinBoxFreq->setValue(ConfigUSBPort.adc_freq);
    ui->spinBoxTimeout->setValue(ConfigUSBPort.timeOut);
    ui->spinBoxTreshold->setValue(getTreshold());
    ui->spinBoxDUP->setValue(getDUPChannelSettings());
}

void WidgetSettings::on_pushButtonAccept_clicked()
{
    QString datadir = "Settings";
    if (!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    QSettings settings((datadir.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    bool ok;
    auto PID = QString("0x" + ui->lineEditPID->text()).toInt(&ok, 16);
    auto VID = QString("0x" + ui->lineEditVID->text()).toInt(&ok, 16);
    settings.setValue("PID", PID);
    settings.setValue("VID", VID);
    settings.setValue("timeout", ui->spinBoxTimeout->value());
    settings.setValue("freq", ui->spinBoxFreq->value());
    settings.setValue("count", ui->spinBoxCount->value());
    settings.setValue("treshold",ui->spinBoxTreshold->value());
    settings.setValue("dup", ui->spinBoxDUP->value());
    settings.sync();
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
