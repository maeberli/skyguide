/**
  * Class declaration file of SkyComponent.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef VECTOROPERATIONS_H
#define VECTOROPERATIONS_H

//include Qt-headers
#include <QDebug>

//include c++ headers
#include <cmath>

namespace CalculatorImpl
{

/**
  * Represents a vector in three dimensions.
  */
struct Vect3D
{
    /**
      * Constructor, setup struct.
      */
    Vect3D(double x=0, double y=0, double z=0) : x(x),y(y),z(z) { }
    double x;   //< x component of vector
    double y;   //< y component of vector
    double z;   //< z component of vector
};

/**
  * QDebug output stream operator to write a QDebug stream.
  *
  * @param dbg          QDebug stream to write in.
  * @param v            Vector to write.
  */
QDebug operator<<(QDebug dbg, const Vect3D& v);

/**
  * Abstract static class which contains static methods for Vector operations.
  */
class VectorOperations
{
public:

    /**
      * Calculates the cross product of two vectors (v1 x v2)
      *
      * @param v1       lefthanded vector in cross operation.
      * @param v2       righthanded vector in cross operation.
      * @return         Result vector of the operation.
      */
    static Vect3D crossProduct(const Vect3D& v1, const Vect3D& v2)
    {
        Vect3D rv;
        rv.x =  v1.y*v2.z - v1.z*v2.y;
        rv.y =  v1.z*v2.x - v1.x*v2.z;
        rv.z =  v1.x*v2.y - v1.y*v2.x;
        return rv;
    }

    /**
      * Calculates the scalar product of the two vectors.
      *
      * @param v1       First vector of the operation.
      * @param v2       Second vector of the operation.
      * @return         Signed result value.
      */
    static double scalarProduct(const Vect3D& v1, const Vect3D& v2)
    {
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    /**
      * Calculates the norm of a vector.
      *
      * @param v        The norm of this vector will be calculated.
      * @return         Norm of the vector v.
      */
    static double getNorm(const Vect3D& v)
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }

    /**
      * Calculates the unit vector of a vector.
      *
      * @param v        The unit of this vector will be calculated.
      * @return         Unit vector of v passed as argument.
      */
    static Vect3D getUnitVector(const Vect3D& v)
    {
        Vect3D rv;
        double norm = getNorm(v);

        rv.x = v.x / norm;
        rv.y = v.y / norm;
        rv.z = v.z / norm;

        return rv;
    }


    /**
      * Calculates the angle between two vectors.
      *
      * @param v1       First vector of operation.
      * @param v2       Second vector of operation.
      * @return         Angle beetween 0 and PI.
      */
    static double getAngleBetween(
            const Vect3D& v1,
            const Vect3D& v2);

    /**
      * Calculates the compass direction of the vector v1, based on the vector north and east.
      *
      * @param v1       Vector in 3 dimension, which will be projectet on north and east.
      * @param north    Vector which points to the north.
      * @param east     Vector which points to the east.
      */
    static double getCompassDirection(
            const Vect3D& v1,
            const Vect3D& north,
            const Vect3D& east);

    /**
      * Methode calculates the right ascension of a vector.
      *
      * @param v        The right ascension of this vector will be calculated.
      * @return         Right ascension beetween 0 and 2*PI
      **/
    static double getRightAscension(const Vect3D& v);

    /**
      * Converts a value which describes a compass direction (North 0, East PI/2, South PI, West PI*23)
      * to the horizontal azimuth value (North PI, East PI*3/2, South 0, West PI/2)
      *
      */
    static double transformCompDirectionSystem(double compDir);

    /**
      * Converts a right ascension and an inclination into a 3 dimensioned vector.
      *
      * @param rightAscension   Right ascension base.
      * @param inclination      Inclination base.
      * @return                 Vector calculated based on right ascension and inclination.
      */
    static Vect3D getVect3D(double rightAscension, double inclination);

private:
    VectorOperations() {}
};

}
#endif // VECTOROPERATIONS_H
