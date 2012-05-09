#include "skydatabase.h"

SkyDatabase::SkyDatabase(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyDatabase"));
}

QList<SkyElement*>* SkyDatabase::getSkyElements(const SkyRange & range)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("getSkyElements SkyDatabase -> not implemented"));

    QList<SkyElement*>* list = new QList<SkyElement*>();

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
