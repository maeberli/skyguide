#include "skyexternaldevice.h"

SkyExternalDevice::SkyExternalDevice(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyExternalDevice"));
}

SkyExternalDevice::~SkyExternalDevice()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Destructor SkyExternalDevice"));
}

void SkyExternalDevice::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("start SkyExternalDevice -> not implemented"));
}

void SkyExternalDevice::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("stop SkyExternalDevice -> not implemented"));
}
