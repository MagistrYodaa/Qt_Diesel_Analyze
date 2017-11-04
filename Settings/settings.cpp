#include "settings.h"

double getTreshold()
{
    QString settingsDIR = "Settings";
    if (!QDir(settingsDIR).exists()){
        QDir().mkdir(settingsDIR);
    }
    QSettings settings((settingsDIR.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    return settings.value("treshold").toDouble();
}

void getUsbSettings(TConfigUSBPort &configUSBPort)
{
    QString settingsDir = "Settings";
    if (!QDir(settingsDir).exists()){
        QDir().mkdir(settingsDir);
    }
    QSettings settings((settingsDir.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    configUSBPort.adc_count = settings.value("count").toInt();
    configUSBPort.adc_freq = settings.value("freq").toInt();
    configUSBPort.pid = settings.value("PID").toInt();
    configUSBPort.vid = settings.value("VID").toInt();
    configUSBPort.timeOut = settings.value("timeout").toInt();
}

void getCountVector(QVector <double> &countVector)
{
    QString datadir = "Settings";
    if (!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    QSettings settings((datadir.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    countVector.reserve(settings.value("count").toInt());
    for (int i = 0; i < settings.value("count").toInt(); i++){
        countVector.push_back(i);// filling vector with number of meterings
    }
}

int getDUPChannelSettings()
{
    QString settingsDIR = "Settings";
    if (!QDir(settingsDIR).exists()){
        QDir().mkdir(settingsDIR);
    }
    QSettings settings((settingsDIR.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    return settings.value("dup").toInt();
}

QString getDUPChannel()
{
    QString settingsDIR = "Settings";
    if (!QDir(settingsDIR).exists()){
        QDir().mkdir(settingsDIR);
    }
    QSettings settings((settingsDIR.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    return QString::fromUtf8(("Channel_" + std::to_string(settings.value("dup").toInt())).c_str());
}
