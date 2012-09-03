#ifndef VECTOROPERATIONS_H
#define VECTOROPERATIONS_H

#include <QDebug>
#include <cmath>

namespace CalculatorImpl
{

struct Vect3D
{
    Vect3D(double x=0, double y=0, double z=0) : x(x),y(y),z(z) { }
    double x;
    double y;
    double z;
};

QDebug operator<<(QDebug dbg, const Vect3D& v);

class VectorOperations
{
public:
    static Vect3D crossProduct(const Vect3D& v1, const Vect3D& v2)
    {
        Vect3D rv;
        rv.x =  v1.y*v2.z - v1.z*v2.y;
        rv.y =  v1.z*v2.x - v1.x*v2.z;
        rv.z =  v1.x*v2.y - v1.y*v2.x;
        return rv;
    }

    static double scalarProduct(const Vect3D& v1, const Vect3D& v2)
    {
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    static double getNorm(const Vect3D& v)
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }

    static Vect3D getUnitVector(const Vect3D& v)
    {
        Vect3D rv;
        double norm = getNorm(v);

        rv.x = v.x / norm;
        rv.y = v.y / norm;
        rv.z = v.z / norm;

        return rv;
    }


    static double getAngleBetween(
            const Vect3D& v1,
            const Vect3D& v2);

    static double getCompassDirection(
            const Vect3D& v1,
            const Vect3D& north,
            const Vect3D& east);

    static double getRightAscension(const Vect3D& v);

    static double transformCompDirectionSystem(double compDir);

    static Vect3D getVect3D(double rightAscension, double inclination);

private:
    VectorOperations(){}
};

}
#endif // VECTOROPERATIONS_H
