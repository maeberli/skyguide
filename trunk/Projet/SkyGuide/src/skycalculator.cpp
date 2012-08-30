#include "skycalculator.h"

#include <QDebug>

SkyCalculator::SkyCalculator(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
}

QList<SkyGuiElement*>* SkyCalculator::convert2GuiElements(const QList<SkyElement*> &elements)
{
    QList<SkyGuiElement*>* guiElements =  new QList<SkyGuiElement*>();

    foreach(SkyElement* element, elements)
    {
        guiElements->append(new SkyGuiElement(*element,0,0));
    }

    return guiElements;
}

