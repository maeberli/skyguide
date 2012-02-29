#include "skycore.h"

//todo: remove include
#include "skylogger.h"

SkyCore::SkyCore(QObject *parent) :
    QObject(parent)
{
    SKYLOGGER::SkyLogger tmp;

    tmp.logMessage(SKYLOGGER::INFO, QString("asdfjladfjlkasd"));

    tmp.logMessage(SKYLOGGER::WARNING, QString("asdfjladfjlkasd"));
    tmp.logMessage(SKYLOGGER::VERBOSE, QString("asdfjladfjlkasd"));
    tmp.logMessage(SKYLOGGER::DEBUG, QString("asdfjladfjlkasd"));
}
