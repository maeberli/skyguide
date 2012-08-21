#include "skyguielement.h"

SkyGuiElement::SkyGuiElement(SkyElement& skyelement, double positionX, double positionY) : SkyElement(skyelement)
{
    p_positionX = positionX;
    p_positionY = positionY;
}

double SkyGuiElement::getPositionX()
{
    return this->p_positionX;
}

double SkyGuiElement::getPositionY()
{
    return this->p_positionY;
}

void SkyGuiElement::setPositionX(double newX)
{
    this->p_positionX = newX;
}

void SkyGuiElement::setPositionY(double newY)
{
    this->p_positionY = newY;
}
