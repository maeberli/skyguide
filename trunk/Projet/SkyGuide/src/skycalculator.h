#ifndef SKYCALCULATOR_H
#define SKYCALCULATOR_H

#include <skycomponent.h>
#include <skyrange.h>
#include <skyelement.h>
#include <skyguielement.h>

#include "CalculatorImpl/vectoroperations.h"
using namespace CalculatorImpl;

class SkyCalculator : public SkyComponent
{
    Q_OBJECT
public:
    SkyCalculator(SkyConfiguration* config, QObject *parent = 0);

    QList<SkyGuiElement*>* convert2GuiElements(const QList<SkyElement*> & elements);


    Vect3D crossProduct(const Vect3D& v1, const Vect3D& v2) const
    {
        return VectorOperations::crossProduct(v1,v2);
    }

    double scalarProduct(const Vect3D& v1, const Vect3D& v2) const
    {
        return VectorOperations::scalarProduct(v1,v2);
    }

    double getNorm(const Vect3D& v) const
    {
        return VectorOperations::getNorm(v);
    }

    Vect3D getUnitVector(const Vect3D& v) const
    {
        return VectorOperations::getUnitVector(v);
    }

    /**
      * calculates the angle beetween two vectors with the scalar product.
      *
      * @return     angle between the two vectors
      */
    double getAngleBetween(
            const Vect3D& v1,
            const Vect3D& v2) const
    {
        return VectorOperations::getAngleBetween(v1,v2);
    }

    /**
      * returns the angle beetween north and the vector v.
      * value returned is in range 0 - (2*PI)
      * NORTH: 0 ou 2PI
      * EAST:  PI/2
      * SOUTH: PI
      * WEST:  3*PI/2
      */
    double getCompassDirection(
            const Vect3D& v1,
            const Vect3D& north = Vect3D(0,1,0),
            const Vect3D& east = Vect3D(1,0,0)) const
    {
        return VectorOperations::getCompassDirection(v1,north,east);
    }

    /**
      * Calculates the right ascension of a vector which is defined in a cartesian coordinate system.
      * returns angle in range [0;(2*PI)]
      * North: +z
      * SOUT:  -z
      * CENTER of earth (0,0,0)
      * intersection meridan null and equator in axe of +x
      */
    double getRightAscension(const Vect3D& v) const
    {
        return VectorOperations::getRightAscension(v);
    }

    /**
      * Transforms a direction angle between the two system with north as zero reference
      * and south as zero refrence.
      *
      * @param compDir  compassdirection to transform ( range [0;(2*PI)] )
      *
      * @return         transformed compass direction ( range [0;(2*PI)] )
      */
    double transformCompDirectionSystem(double compDir) const
    {
        return VectorOperations::transformCompDirectionSystem(compDir);
    }

    /**
      * Calculates the vector (direction) defined in a cartesian coordinate system out of rigth ascension and inclination.
      * returns angle in ( range [0;(2*PI)] )
      * North: +z
      * SOUT:  -z
      * CENTER of earth (0,0,0)
      * intersection meridan null and equator in axe of +x
      */
    Vect3D getVect3D(double rightAscension, double inclination) const
    {
        return VectorOperations::getVect3D(rightAscension,inclination);
    }

signals:

public slots:
    virtual void start() { }
    virtual void stop() { }

};

#endif // SKYCALCULATOR_H
