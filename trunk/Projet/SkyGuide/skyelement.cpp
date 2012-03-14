#include "skyelement.h"

SkyElement::SkyElement(double rightAscension,
                       double declinasion,
                       QString greekLetter,
                       QString constellation,
                       int distancelightYears,
                       double magnitude)
{
    this->p_rightAscension = rightAscension;
    this->p_declinasion = declinasion;
    this->p_greekLetter = greekLetter;
    this->p_constellation = constellation;
    this->p_distanceLightYears = distancelightYears;
    this->p_magnitude = magnitude;
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

