#include "skygui.h"

SkyGui::SkyGui(QObject *parent) :
    SkyComponent(parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyGui"));
}

SkyGui::~SkyGui()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Deconstructor SkyGui"));
}

void SkyGui::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("start SkyGui -> not implemented"));
}

void SkyGui::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("stop SkyGui -> not implemented"));

}

void SkyGui::showWarning(const QString &message)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("showWarning slot SkyGui. Message: %1").arg(message));
}

void SkyGui::showError(const QString &message)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("showError slot SkyGui. Message: %1").arg(message));
}

void SkyGui::showInfo(const QString &message)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("showInfo slot SkyGui. Message: %1").arg(message));
}

void SkyGui::updateAffichage(QList<SkyGuiElement *> elements)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("updateAffichage slot SkyGui -> not implemented"));
}
