#include "skycalculator.h"

SkyCalculator::SkyCalculator(QObject *parent) :
    SkyComponent(parent)
{
}

void SkyCalculator::getSkyRange(int positionData, int direction, int slope, int inclLefRight)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("getSkyRange SkyCalculator"));
}

QList<SkyGuiElement*> SkyCalculator::convert2GuiElements(const QList<SkyElement *> &elements)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("convert2GuiElements SkyCalculator"));

    QList<SkyGuiElement*> guiElements;

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
