#include "skycalculator.h"

SkyCalculator::SkyCalculator(QObject *parent) :
    SkyComponent(parent)
{
}

SkyRange SkyCalculator::getSkyRange(int positionData, int direction, int slope, int inclLefRight)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("getSkyRange SkyCalculator -> not implemented"));

    return SkyRange(0,0);
}

QList<SkyGuiElement*>* SkyCalculator::convert2GuiElements(const QList<SkyElement*> &elements)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("convert2GuiElements SkyCalculator -> not implemented"));

    QList<SkyGuiElement*>* guiElements =  new QList<SkyGuiElement*>();

    foreach(SkyElement* element, elements)
    {
        guiElements->append(new SkyGuiElement(*element,0,0));
    }

    return guiElements;
}

void SkyCalculator::start()
{
    logMessage(SKYLOGGER::VERBOSE, tr("start SkyLogger -> not implemented (no use)."));
}

void SkyCalculator::stop()
{
    logMessage(SKYLOGGER::VERBOSE, tr("stop SkyLogger -> not implemented (no use)."));
}
