#include "skycalculator.h"

#include <QDebug>

QDebug operator<<(QDebug dbg, const Vect3D& v)
{
    dbg << "(" << v.x << "," << v.y << "," << v.z << ")";
    return dbg;
}

SkyCalculator::SkyCalculator(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
}

QList<SkyGuiElement*>* SkyCalculator::convert2GuiElements(const QList<SkyElement*> &elements)
{
    QList<SkyGuiElement*>* guiElements =  new QList<SkyGuiElement*>();

    foreach(SkyElement* element, elements)
    {
        guiElements->append(new SkyGuiElement(*element,0,0));
    }

    return guiElements;
}

/**
  * calculates the angle beetween two vectors with the scalar product.
  *
  * @return     angle between the two vectors
  */
double SkyCalculator::getAngleBetween(
        const Vect3D& v1,
        const Vect3D& v2) const
{
    return acos(scalarProduct(v1,v2) / ( getNorm(v1)*getNorm(v2) ));
}

/**
  * returns the angle beetween north and the vector v.
  * value returned is in range 0 - (2*PI)
  * NORTH: 0 ou 2PI
  * EAST:  PI/2
  * SOUTH: PI
  * WEST:  3*PI/2
  */
double SkyCalculator::getCompassDirection(
        const Vect3D& v,
        const Vect3D& north,
        const Vect3D& east) const
{
    double angle = atan2(scalarProduct(v,east), scalarProduct(v,north)) + M_PI;

    if(angle < 0)
        return angle + 2*M_PI;
    else
        return angle;
}

/**
  * Calculates the right ascension of a vector which is defined in a cartesian coordinate system.
  * returns angle in range [0;(2*PI)]
  * North: +z
  * SOUT:  -z
  * CENTER of earth (0,0,0)
  * intersection meridan null and equator in axe of +x
  */
double SkyCalculator::getRightAscension(const Vect3D& v) const
{
    double angle = atan2(scalarProduct(v,Vect3D(0,1,0)), scalarProduct(v,Vect3D(1,0,0)));

    if(angle < 0)
        return angle + 2*M_PI;
    else
        return angle;
}

/**
  * Transforms a direction angle between the two system with north as zero reference
  * and south as zero refrence.
  *
  * @param compDir  compassdirection to transform ( range [0;(2*PI)] )
  *
  * @return         transformed compass direction ( range [0;(2*PI)] )
  */
double SkyCalculator::transformCompDirectionSystem(double compDir) const
{
    return (compDir + M_PI > 2*M_PI ? compDir-M_PI : compDir+M_PI);
}

/**
  * Calculates the vector (direction) defined in a cartesian coordinate system out of rigth ascension and inclination.
  * returns angle in ( range [0;(2*PI)] )
  * North: +z
  * SOUT:  -z
  * CENTER of earth (0,0,0)
  * intersection meridan null and equator in axe of +x
  */
Vect3D SkyCalculator::getVect3D(double rightAscension, double inclination) const
{
    Vect3D rv;
    rv.x = sin(M_PI/2 - inclination)*cos(rightAscension);
    rv.y = sin(M_PI/2 - inclination)*sin(rightAscension);
    rv.z = cos(M_PI/2 - inclination);
    return rv;
}
