#include "skydatabase.h"

SkyDatabase::SkyDatabase(QObject *parent) :
    SkyComponent(parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyDatabase"));
}

QList<SkyElement*> SkyDatabase::getSkyElements(const SkyRange & range)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("getSkyElements SkyDatabase"));

    QList<SkyElement*> list;

    return list;
}

void SkyDatabase::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Start SkyDatabase -> not implemented"));
}

void SkyDatabase::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Stop SkyDatabase -> not implemented"));
}
