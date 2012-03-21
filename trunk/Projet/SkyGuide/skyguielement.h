#ifndef SKYGUIELEMENT_H
#define SKYGUIELEMENT_H

#include <skyelement.h>

class SkyGuiElement : public SkyElement
{
public:
    explicit SkyGuiElement(const SkyElement& skyelement, int positionX, int positionY);

    int getPositionX();
    int getPositionY();

private:
    SkyGuiElement(const SkyElement& skyelement);

    int p_positionX;
    int p_positionY;
};

#endif // SKYGUIELEMENT_H
