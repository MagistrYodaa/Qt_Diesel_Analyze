#ifndef DIESELTYPE_H
#define DIESELTYPE_H

#include <QString>
#include <QVector>

class DieselType
{
private:
    int angleWedge;
    QString dieselMark;
    int cylindersCount;
    int tacticity;

    QString counstuctionType;
    QVector <int> workOrder;
    double cylindersDiameter;
    double pistonStroke;
    double conrodLenght;

    DieselType() {}
    DieselType(const DieselType&);
    DieselType& operator=(DieselType&);

public:
    int getTacticity() const;
    void setTacticity(int value);
    int getCylindersCount() const;
    void setCylindersCount(int value);
    QString getDieselMark() const;
    void setDieselMark(const QString &value);
    int getAngleWedge() const;
    void setAngleWedge(int value);
    QString getCounstuctionType() const;
    void setCounstuctionType(const QString &value);
    double getCylindersDiameter() const;
    void setCylindersDiameter(double value);
    double getPistonStroke() const;
    void setPistonStroke(double value);
    double getConrodLenght() const;
    void setConrodLenght(double value);
    QVector<int> getWorkOrder() const;
    void setWorkOrder(const QVector<int> &value);

    static DieselType& getInstance() {
            static DieselType instance;
            return instance;
        }    
};

#endif // DIESELTYPE_H
