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

    double getRightAscension();
    double getDeclinasion();
    QString getGreekLetter();
    QString getConstellation();
    int getDistanceLightYears();
    double getMagnitude();


private:
    double p_rightAscension;
    double p_declinasion;
    QString p_greekLetter;
    QString p_constellation;
    int p_distanceLightYears;
    double p_magnitude;

};

#endif // SKYELEMENT_H
