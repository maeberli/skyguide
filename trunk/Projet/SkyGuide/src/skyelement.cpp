/**
  * Class implementation file of SkyElement.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "skyelement.h"

#include <QString>

SkyElement::SkyElement(double rightAscension,
                       double declination,
                       QString greekLetter,
                       QString constellation,
                       int distancelightYears,
                       double magnitude)
{
    this->p_rightAscension = rightAscension * 3.14159265 / 180;
    this->p_declinasion = declination * 3.14159265 / 180;
    this->p_greekLetter = greekLetter;
    this->p_constellation = constellation;
    this->p_distanceLightYears = distancelightYears;
    this->p_magnitude = magnitude;
    p_azimuth = 0.0;
    p_altitude = 0.0;
}

SkyElement::SkyElement(const SkyElement &skyelement)
{
    p_rightAscension = skyelement.p_rightAscension;
    p_declinasion = skyelement.p_declinasion;
    p_greekLetter = skyelement.p_greekLetter;
    p_constellation = skyelement.p_constellation;
    p_distanceLightYears = skyelement.p_distanceLightYears;
    p_magnitude = skyelement.p_magnitude;
    p_azimuth = skyelement.p_azimuth;
    p_altitude = skyelement.p_altitude;
}

double SkyElement::getRightAscension()
{
    return this->p_rightAscension;
}

double SkyElement::getDeclinasion()
{
    return this->p_declinasion;
}

QString SkyElement::getGreekLetter()
{
    return this->p_greekLetter;
}

QString SkyElement::getConstellation()
{
    return this->p_constellation;
}

int SkyElement::getDistanceLightYears()
{
    return this->p_distanceLightYears;
}

double SkyElement::getMagnitude()
{
    return this->p_magnitude;
}
double SkyElement::getAzimuth()
{
    return p_azimuth;
}
double SkyElement::getAltitude()
{
    return p_altitude;
}
void SkyElement::setAzimuth(double azimuth)
{
    p_azimuth = azimuth;
}
void SkyElement::setAltitude(double altitude)
{
    p_altitude = altitude;
}

