/**
  * Class declaration file of SkyCalculator.
  *
  * @author      Matthieu Rossier / Aeberli Marco
  *
  * @copyright   Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYCALCULATOR_H
#define SKYCALCULATOR_H

//include SkyGuide specific headers
#include "skycomponent.h"
#include "skyelement.h"
#include "skyguielement.h"
#include "CalculatorImpl/vectoroperations.h"

using namespace CalculatorImpl;

/**
  * Class who represent calcul.
  */
class SkyCalculator : public SkyComponent
{
    Q_OBJECT
public:
    /**
      * Constructor, creates and initialize the object.
      *
      * @param config     Represent the file configuration.
      * @param parent     Represent object who inialize it.
      */
    SkyCalculator(SkyConfiguration* config, QObject *parent = 0);

    /**
      * Calcul angle hour.
      */
    static double getAngleHour();

    /**
      * Transform in system coordinate horizontale with (right ascension, declinaison, latitude, longitude and angle hour).
      */
    static void toHorizontalCoord(SkyElement* star, double angle, double latitude, double longitude);

    /**
      * Load to memory contains of file database (SkyGuide.db).
      */
    static void projectOnPlane(SkyElement* star, double* x, double* y, int factor);

    /**
      * Load to memory contains of file database (SkyGuide.db).
      */
    static void projectOnPlane(double azimuth, double height, double* x, double* y, int factor);


    /**
      * Calculates the cross product of two vectors (v1 x v2)
      *
      * @param v1       lefthanded vector in cross operation.
      * @param v2       righthanded vector in cross operation.
      * @return         Result vector of the operation.
      */
    Vect3D crossProduct(const Vect3D& v1, const Vect3D& v2) const
    {
        return VectorOperations::crossProduct(v1,v2);
    }

    /**
      * Calculates the scalar product of the two vectors.
      *
      * @param v1       First vector of the operation.
      * @param v2       Second vector of the operation.
      * @return         Signed result value.
      */
    double scalarProduct(const Vect3D& v1, const Vect3D& v2) const
    {
        return VectorOperations::scalarProduct(v1,v2);
    }

    /**
      * Calculates the norm of a vector.
      *
      * @param v        The norm of this vector will be calculated.
      * @return         Norm of the vector v.
      */
    double getNorm(const Vect3D& v) const
    {
        return VectorOperations::getNorm(v);
    }

    /**
      * Calculates the unit vector of a vector.
      *
      * @param v        The unit of this vector will be calculated.
      * @return         Unit vector of v passed as argument.
      */
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
    void start() { }
    void stop() { }

};

#endif // SKYCALCULATOR_H
