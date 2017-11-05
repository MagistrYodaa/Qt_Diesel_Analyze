#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H

#include <QSettings>
#include <QVector>
#include <QDir>
#include "ModBus/include/ModBusUSB.h"

class Settings
{
private:
    QSettings* settings_;
    double treshold_;
    int dupChannel_;
    int PID_;
    int VID_;
    int timeOut_;
    int freq_;
    int count_;
public:
    Settings();
    QString getDUPChannelString();
    double getTreshold() const;
    void setTreshold(double getTreshold);
    int getDupChannel() const;
    void setDupChannel(int getDupChannel);
    int getPID() const;
    void setPID(int getPID);
    int getVID() const;
    void setVID(int getVID);
    int getTimeOut() const;
    void setTimeOut(int getTimeOut);
    int getFreq() const;
    void setFreq(int getFreq);
    int getCount() const;
    void setCount(int getCount);
    void sync();
    void getCountVector(QVector<double> &countVector);
    void getUsbSettings(TConfigUSBPort &configUSBPort);
    ~Settings();
};

#endif // SETTINGSCLASS_H
