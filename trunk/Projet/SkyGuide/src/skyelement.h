#ifndef SKYELEMENT_H
#define SKYELEMENT_H

#include <QString>

class SkyElement
{
public:
    SkyElement(
        double rightAscension,
        double declinasion,
        QString greekLetter,
        QString constellation,
        int distancelightYears,
        double magnitude);
    SkyElement(SkyElement& skyelement);


    double getRightAscension();
    double getDeclinasion();
    QString getGreekLetter();
    QString getConstellation();
    int getDistanceLightYears();
    double getMagnitude();
    double getAzimuth();
    double getHeight();
    void setAzimuth(double azimuth);
    void setHeight(double height);


protected:
    double p_rightAscension;
    double p_declinasion;
    QString p_greekLetter;
    QString p_constellation;
    int p_distanceLightYears;
    double p_magnitude;
    double p_azimuth;
    double p_height;

};

#endif // SKYELEMENT_H
