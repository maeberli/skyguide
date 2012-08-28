#include "skycalculator.h"

#include <QDebug>

QDebug operator<<(QDebug dbg, const Vect3D& v)
{
    dbg << "(" << v.x << "," << v.y << "," << v.z << ")";
    return dbg;
}

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

