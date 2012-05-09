#include "skyguielement.h"

SkyGuiElement::SkyGuiElement(const SkyElement& skyelement, int positionX, int positionY):
    SkyElement(skyelement)
{
    p_positionX = positionX;
    p_positionY = positionY;
}


int SkyGuiElement::getPositionX()
{
    return this->p_positionX;
}

int SkyGuiElement::getPositionY()
{
    return this->p_positionY;
}
