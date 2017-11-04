#ifndef SETTINGS_H
#define SETTINGS_H

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
    double treshold() const;
    void setTreshold(double treshold);
    int dupChannel() const;
    void setDupChannel(int dupChannel);
    int PID() const;
    void setPID(int PID);
    int VID() const;
    void setVID(int VID);
    int timeOut() const;
    void setTimeOut(int timeOut);
    int freq() const;
    void setFreq(int freq);
    int count() const;
    void setCount(int count);
    void sync();
    void getCountVector(QVector<int> &countVector);
    static void getUsbSettings(TConfigUSBPort &configUSBPort);
    ~Settings();
};

#endif // SETTINGS_H
