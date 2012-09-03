/**
  * Class declaration file of SkyElement.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYELEMENT_H
#define SKYELEMENT_H

//include Qt-headers
#include <QString>

/**
  * This class represents a element of the sky, with its proper informations.
  */
class SkyElement
{
public:
    /**
      * Constructort, create object.
      *
      * @param rightAscension       right ascension in degrees of the the element.
      * @param declinasion          declination in degrees of the element.
      * @param greekLetter          greekLetter of the element.
      * @param constellation        constellation information of the element.
      * @param distancelightYears   distance information in lightyears of the element.
      * @param magnitude            magnitude information of the element.
      */
    SkyElement(
        double rightAscension,
        double declination,
        QString greekLetter,
        QString constellation,
        int distancelightYears,
        double magnitude);

    /**
      * Copy constructor.
      *
      * @param skyelement           Element to copy.
      */
    SkyElement(const SkyElement& skyelement);


    /**
      * Accessor, returns the right-ascension in radian.
      *
      * @return     right-ascension in radian.
      */
    double getRightAscension();

    /**
      * Accessor, returns the declinasion in radian.
      *
      * @return     declination in radian.
      */
    double getDeclination();

    /**
      * Accessor, returns the greek-letter.
      *
      * @return     greek-letter of element.
      */
    QString getGreekLetter();

    /**
      * Accessor, returns the constellation information.
      *
      * @return     constellation information of element.
      */
    QString getConstellation();

    /**
      * Accessor, returns the distance in light-years.
      *
      * @return     distance in light-years of element.
      */
    int getDistanceLightYears();

    /**
      * Accessor, returns the magnitude.
      *
      * @return     magnitude of element.
      */
    double getMagnitude();


    /**
      * Accessor, returns the azimuth.
      *
      * @return     azimuth in radian of element.
      */
    double getAzimuth();

    /**
      * Accessor, returns the altitude.
      *
      * @return     altitude in radion of element.
      */
    double getAltitude();

    /**
      * Accessor, sets the azimuth information of a element.
      *
      * @param azimuth  azmimuth information to set.
      */
    void setAzimuth(double azimuth);

    /**
      * Accessor, set the altitude information of a element.
      *
      * @param altitude   altitude information to set.
      */
    void setAltitude(double altitude);


protected:
    double p_rightAscension;
    double p_declination;
    QString p_greekLetter;
    QString p_constellation;
    int p_distanceLightYears;
    double p_magnitude;
    double p_azimuth;
    double p_altitude;

};

#endif // SKYELEMENT_H
