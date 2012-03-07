#include "skycore.h"

using namespace SKYLOGGER;

SkyCore::SkyCore(QObject *parent) :
    QObject(parent)
{
    p_logger = new SkyLogger(parent);
    p_database = new SkyDatabase(parent);
    p_calculator = new SkyCalculator(parent);
    p_externalDevice = new SkyExternalDevice(parent);

    connect(p_database, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));

    connect(p_calculator, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));

    connect(p_externalDevice, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
}

SkyCore::~SkyCore()
{
    delete p_database;
    delete p_logger;
    delete p_calculator;
    delete p_externalDevice;
}
