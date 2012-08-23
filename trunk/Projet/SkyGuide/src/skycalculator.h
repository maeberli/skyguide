#ifndef SKYCALCULATOR_H
#define SKYCALCULATOR_H

#include <skycomponent.h>
#include <skyrange.h>
#include <skyelement.h>
#include <skyguielement.h>

#include <math.h>

struct Vect3D
{
    Vect3D(double _x=0, double _y=0, double _z=0) : x(_x),y(_y),z(_z) { }
    double x;
    double y;
    double z;
};

class SkyCalculator : public SkyComponent
{
    Q_OBJECT
public:
    SkyCalculator(SkyConfiguration* config, QObject *parent = 0);

    QList<SkyGuiElement*>* convert2GuiElements(const QList<SkyElement*> & elements);


    Vect3D crossProduct(const Vect3D& v1, const Vect3D& v2) const
    {
        Vect3D rv;
        rv.x =  v1.y*v2.z - v1.z*v2.y;
        rv.y =  v1.z*v2.x - v1.x*v2.z;
        rv.z =  v1.x*v2.y - v1.y*v2.x;
        return rv;
    }

    double scalarProduct(const Vect3D& v1, const Vect3D& v2) const
    {
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    double getNorm(const Vect3D& v) const
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }

    Vect3D getUnitVector(const Vect3D& v) const
    {
        Vect3D rv;
        double norm = getNorm(v);

        rv.x = v.x / norm;
        rv.y = v.y / norm;
        rv.z = v.z / norm;

        return rv;
    }

    double getAngleBetween(
            const Vect3D& v1,
            const Vect3D& v2) const;

    double getCompassDirection(
            const Vect3D& v1,
            const Vect3D& north = Vect3D(0,1,0),
            const Vect3D& east = Vect3D(1,0,0)) const;

    double getRightAscension(const Vect3D& v) const;

    double transformCompDirectionSystem(double compDir) const;

    Vect3D getVect3D(double rightAscension, double inclination) const;

signals:

public slots:
    virtual void start();
    virtual void stop();

};

#endif // SKYCALCULATOR_H
