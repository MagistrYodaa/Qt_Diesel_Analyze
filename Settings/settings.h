#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVector>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <ModBus/include/ModBusUSB.h>
#include <DieselType/dieseltype.h>

void getUsbSettings(TConfigUSBPort &configUSBPort);

void getCountVector(QVector <double> &countVector);

void saveDefaultDiesel();

void getDefaultDiesel();

int getDUPChannelSettings();

double getTreshold();

QString getDUPChannel();

#endif // SETTINGS_H
