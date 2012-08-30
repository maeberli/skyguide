#include "vectoroperations.h"

namespace CalculatorImpl
{

QDebug operator<<(QDebug dbg, const Vect3D& v)
{
    dbg << "(" << v.x << "," << v.y << "," << v.z << ")";
    return dbg;
}

double VectorOperations::getAngleBetween(
        const Vect3D& v1,
        const Vect3D& v2)
{
    return acos(scalarProduct(v1,v2) / ( getNorm(v1)*getNorm(v2) ));
}

double VectorOperations::getCompassDirection(
        const Vect3D& v,
        const Vect3D& north,
        const Vect3D& east)
{
    double angle = atan2(scalarProduct(v,east), scalarProduct(v,north)) + M_PI;

    if(angle < 0)
        return angle + 2*M_PI;
    else
        return angle;
}

double VectorOperations::getRightAscension(const Vect3D& v)
{
    double angle = atan2(scalarProduct(v,Vect3D(0,1,0)), scalarProduct(v,Vect3D(1,0,0)));

    if(angle < 0)
        return angle + 2*M_PI;
    else
        return angle;
}

double VectorOperations::transformCompDirectionSystem(double compDir)
{
    return (compDir + M_PI > 2*M_PI ? compDir-M_PI : compDir+M_PI);
}

Vect3D VectorOperations::getVect3D(double rightAscension, double inclination)
{
    Vect3D rv;
    rv.x = sin(M_PI/2 - inclination)*cos(rightAscension);
    rv.y = sin(M_PI/2 - inclination)*sin(rightAscension);
    rv.z = cos(M_PI/2 - inclination);
    return rv;
}

}
