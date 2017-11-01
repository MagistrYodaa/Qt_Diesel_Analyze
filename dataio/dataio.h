#ifndef DATAREAD_H
#define DATAREAD_H

#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <cstdlib>
#include <cmath>
#include <QDir>
#include <QDebug>
#include <QPen>
#include <QMessageBox>
#include <string>
#include "Spline/spline.h"
#include "Settings/settings.h"
#include "DieselType/dieseltype.h"


typedef struct
{
    unsigned int    adc_channels;
    unsigned int    adc_count;
    unsigned char   adc_freq;
    unsigned short  adc_buff[100000];
}TADC_Data_file;

bool readFromFile(QVector <QVector <double>> &vector_container, QVector<int> usedChannels, QString &answer);

bool readFromFile(QMap <QString, QVector<double>> &map_container, QVector <int> usedChannels, QString &answer);

bool readFromADC(QVector <QVector <double>> &vector_container, QVector<int> usedChannels, QString &answer);

bool readFromADC(QMap <QString, QVector<double>> &map_container, QVector<int> usedChannels, QString &answer);

void getIndicesVector(QVector<double> &dataVector, QVector <int> &indicesVector);

void slimimngIndicesVector(QVector <int> &indicesVector, int &enterAngle);

int getVMTAngle(QVector <int> &indicesVector, QVector <double> &dataVector);

void getVMTDataVector(int VMT, QVector <int> &indicesVector, QVector <double> &dataVector, QVector<double> &vmtVector);

int getAverageIndex(QVector <int> indexes);

void getOneVectorFromSeveral(QVector<QVector<double>> &bigVector, QVector <double> &newVector);

void getAproxVMTVector(QVector <double> &oldVector, double angleSegementNew = 0.5);

void shiftCorrecting(QVector <double> &oldVector);

bool addNewDiesel(const QVariantMap &newDiesel);

bool saveVMT(int VMT);

int getVMTAngle();

void deleteDiesel(const QString &dieselname);

QStringList getDieselsList();

QVector<QVariantMap> getDieselsMap(bool &ok);

QVector<QPen> getColors();

void getChannelsDataMap(QMap<QString, QVector<double>> &mapContainer, int VMT, QVector<int> indicesVector, int channel);

QVector <double> getAnglesVector();

#endif // DATAREAD_H
