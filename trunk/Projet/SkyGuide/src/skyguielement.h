/**
  * Class declaration file of SkyGuiElement.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYGUIELEMENT_H
#define SKYGUIELEMENT_H

//include Qt-headers
#include <QString>

//include SkyGuide specific headers
#include <skyelement.h>

/**
  * This class represents a SkyGuiElement that is prepared to show on gui.
  *
  * It inherits from SkyElement and provides the addional functionalty
  * to get and set the x and y coordinates.
  */
class SkyGuiElement : public SkyElement
{
public:
    /**
      * Constructor, creates object.
      *
      * @param skyelement   skyelement which contains the base informations.
      * @param positionX    x coordinate of the element.
      * @param positionY    y coordinate of the element.
      */
    explicit SkyGuiElement(const SkyElement& skyelement, double positionX, double positionY);

    /**
      * Accessor, returns the x coordinate.
      *
      * @return             x coordinate of the element.
      */
    double getPositionX();

    /**
      * Accessor, returns the y coordinate.
      *
      * @return             y coordinate of the element.
      */
    double getPositionY();

    /**
      * Accessor, sets the x coordinate.
      *
      * @param newX         x coordinate to set.
      */
    void setPositionX(double newX);

    /**
      * Accessor, sets the y coordinate.
      *
      * @param newY         y coordiante to set.
      */
    void setPositionY(double newY);

private:
    double p_positionX; //< variable stores x coordinate
    double p_positionY; //< variable stores y coordinate
};

#endif // SKYGUIELEMENT_H
