#ifndef SKYELEMENT_H
#define SKYELEMENT_H

#include <string>

class SkyElement
{
public:
    SkyElement(
        double rightAscension,
        double declinasion,
        std::string greekLetter,
        std::string constellation,
        int distancelightYears,
        double magnitude);
    SkyElement(const SkyElement& skyelement);


    double getRightAscension();
    double getDeclinasion();
    std::string getGreekLetter();
    std::string getConstellation();
    int getDistanceLightYears();
    double getMagnitude();


private:
    double p_rightAscension;
    double p_declinasion;
    std::string p_greekLetter;
    std::string p_constellation;
    int p_distanceLightYears;
    double p_magnitude;

};

#endif // SKYELEMENT_H
