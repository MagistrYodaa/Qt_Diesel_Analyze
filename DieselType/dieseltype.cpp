#include <DieselType/dieseltype.h>

int DieselType::getCylindersCount() const
{
    return cylindersCount;
}

void DieselType::setCylindersCount(int value)
{
    cylindersCount = value;
}

QString DieselType::getDieselMark() const
{
    return dieselMark;
}

void DieselType::setDieselMark(const QString &value)
{
    dieselMark = value;
}

int DieselType::getAngleWedge() const
{
    return angleWedge;
}

void DieselType::setAngleWedge(int value)
{
    angleWedge = value;
}

QString DieselType::getCounstuctionType() const
{
    return counstuctionType;
}

void DieselType::setCounstuctionType(const QString &value)
{
    counstuctionType = value;
}

double DieselType::getCylindersDiameter() const
{
    return cylindersDiameter;
}

void DieselType::setCylindersDiameter(double value)
{
    cylindersDiameter = value;
}

double DieselType::getPistonStroke() const
{
    return pistonStroke;
}

void DieselType::setPistonStroke(double value)
{
    pistonStroke = value;
}

double DieselType::getConrodLenght() const
{
    return conrodLenght;
}

void DieselType::setConrodLenght(double value)
{
    conrodLenght = value;
}

QVector<int> DieselType::getWorkOrder() const
{
    return workOrder;
}

void DieselType::setWorkOrder(const QVector<int> &value)
{
    workOrder = value;
}

int DieselType::getTacticity() const
{
    return tacticity;
}

void DieselType::setTacticity(int value)
{
    tacticity = value;
}
