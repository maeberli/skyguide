#include "skyelement.h"

using namespace std;

SkyElement::SkyElement(double rightAscension,
                       double declinasion,
                       string greekLetter,
                       string constellation,
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

SkyElement::SkyElement(const SkyElement& skyelement)
{
    SkyElement(
                skyelement.p_rightAscension,
                skyelement.p_declinasion,
                skyelement.p_greekLetter,
                skyelement.p_constellation,
                skyelement.p_distanceLightYears,
                skyelement.p_magnitude
                );
}

double SkyElement::getRightAscension()
{
    return this->p_rightAscension;
}

double SkyElement::getDeclinasion()
{
    return this->p_declinasion;
}

string SkyElement::getGreekLetter()
{
    return this->p_greekLetter;
}

string SkyElement::getConstellation()
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

