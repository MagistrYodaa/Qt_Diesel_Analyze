#include "dieseltype.h"

int DieselType::getCylindersCount() const
{
    return cylindersCount_;
}

void DieselType::setCylindersCount(int value)
{
    cylindersCount_ = value;
}

QString DieselType::getDieselMark() const
{
    return dieselMark_;
}

void DieselType::setDieselMark(const QString &value)
{
    dieselMark_ = value;
}

int DieselType::getAngleWedge() const
{
    return angleWedge_;
}

void DieselType::setAngleWedge(int value)
{
    angleWedge_ = value;
}

QString DieselType::getCounstuctionType() const
{
    return counstuctionType_;
}

void DieselType::setCounstuctionType(const QString &value)
{
    counstuctionType_ = value;
}

double DieselType::getCylindersDiameter() const
{
    return cylindersDiameter_;
}

void DieselType::setCylindersDiameter(double value)
{
    cylindersDiameter_ = value;
}

double DieselType::getPistonStroke() const
{
    return pistonStroke_;
}

void DieselType::setPistonStroke(double value)
{
    pistonStroke_ = value;
}

double DieselType::getConrodLenght() const
{
    return conrodLenght_;
}

void DieselType::setConrodLenght(double value)
{
    conrodLenght_ = value;
}

QVector<int> DieselType::getWorkOrder() const
{
    return workOrder_;
}

void DieselType::setWorkOrder(const QVector<int> &value)
{
    workOrder_ = value;
}

void DieselType::saveDefaultDiesel()
{
    QString datadir = "Settings";
    if(!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    QSettings settings((datadir.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);
    settings.setValue("default_diesel_type", dieselMark_);
    settings.sync();
}

bool DieselType::loadDefaultDiesel()
{
    QString datadir = "Settings";
    if (!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    QSettings settings((datadir.toStdString() + "\\settings.ini").c_str(), QSettings::IniFormat);

    QFile file("DieselsTypes\\" + settings.value("default_diesel_type").toString() + ".json");
    if (!file.open(QIODevice::ReadOnly)){
        return false;
    }

    QByteArray data = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    auto diesel = doc.object().toVariantMap();

    auto listOrder = diesel.value("workOrder").toStringList();

    QVector <int> workOrder;
    for (auto item : listOrder) workOrder.push_back(item.toInt());

    angleWedge_ = diesel.value("anglez").toInt();
    dieselMark_ = diesel.value("dieseltype").toString();
    cylindersCount_ = diesel.value("cylinderscount").toInt();
    tacticity_ = diesel.value("tacticity").toInt();
    workOrder_ = workOrder;
    cylindersDiameter_ = diesel.value("cylinderdiameter").toInt();
    pistonStroke_ = diesel.value("pistonstroke").toInt();
    conrodLenght_ = diesel.value("conrodlenght").toInt();

    file.close();

    return true;
}

int DieselType::getTacticity() const
{
    return tacticity_;
}

void DieselType::setTacticity(int value)
{
    tacticity_ = value;
}
