#ifndef SKYGUIELEMENT_H
#define SKYGUIELEMENT_H

#include <QString>
#include <skyelement.h>

class SkyGuiElement : public SkyElement
{
public:
    explicit SkyGuiElement(SkyElement& skyelement, double positionX, double positionY);

    double getPositionX();
    double getPositionY();
    void setPositionX(double newX);
    void setPositionY(double newY);

private:
    // SkyGuiElement(SkyElement& skyelement);

    double p_positionX;
    double p_positionY;
};

#endif // SKYGUIELEMENT_H
