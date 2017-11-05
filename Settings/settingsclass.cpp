#include "settingsclass.h"

Settings::Settings()
{
    QString settingsDIR = "Settings";
    if (!QDir(settingsDIR).exists()){
        QDir().mkdir(settingsDIR);
    }

    settings_ = new QSettings((settingsDIR.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    treshold_ = settings_->value("treshold").toDouble();
    dupChannel_ = settings_->value("dup").toInt();
    PID_ = settings_->value("PID").toInt();
    VID_ = settings_->value("VID").toInt();
    timeOut_ = settings_->value("timeOut").toInt();
    freq_ = settings_->value("freq").toInt();
    count_ = settings_->value("count").toInt();

}

void Settings::getCountVector(QVector<double> &countVector)
{
    countVector.reserve(count_);
    for (int i = 0; i < count_; i++){
        countVector.push_back(i);
    }
}

QString Settings::getDUPChannelString()
{
    return QString("Channel_%1").arg(dupChannel_);
}

double Settings::getTreshold() const
{
    return treshold_;
}

void Settings::setTreshold(double treshold)
{
    treshold_ = treshold;
    settings_->setValue("treshold", treshold_);
    sync();
}

int Settings::getDupChannel() const
{
    return dupChannel_;
}

void Settings::setDupChannel(int dupChannel)
{
    dupChannel_ = dupChannel;
    settings_->setValue("dup", dupChannel_);
    sync();
}

int Settings::getPID() const
{
    return PID_;
}

void Settings::setPID(int PID)
{
    PID_ = PID;
    settings_->setValue("PID", PID_);
    sync();
}

int Settings::getVID() const
{
    return VID_;
}

void Settings::setVID(int VID)
{
    VID_ = VID;
    settings_->setValue("VID", VID_);
    sync();
}

int Settings::getTimeOut() const
{
    return timeOut_;
}

void Settings::setTimeOut(int timeOut)
{
    timeOut_ = timeOut;
    settings_->setValue("timeOut", timeOut_);
    sync();
}

int Settings::getFreq() const
{
    return freq_;
}

void Settings::setFreq(int freq)
{
    freq_ = freq;
    settings_->setValue("freq", freq_);
    sync();
}

int Settings::getCount() const
{
    return count_;
}

void Settings::setCount(int count)
{
    count_ = count;
    settings_->setValue("count", count_);
    sync();
}

void Settings::sync()
{
    settings_->sync();
}

void Settings::getUsbSettings(TConfigUSBPort &configUSBPort)
{
    configUSBPort.adc_count = count_;
    configUSBPort.adc_freq = freq_;
    configUSBPort.pid = PID_;
    configUSBPort.vid = VID_;
    configUSBPort.timeOut = timeOut_;
}

Settings::~Settings()
{
    delete settings_;
}
