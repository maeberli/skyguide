#include "skylogger.h"

#include <QDebug>
#include <QTime>

#define PREFIX QTime::currentTime().toString("hh:mm:ss.zzz")
#define FILENAME "SkyGuide.log"


SKYLOGGER::SkyLogger::SkyLogger(QObject *parent) :
    QObject(parent)
{

    this->p_file = new QFile(FILENAME);

    if(p_file->open(QIODevice::Append |  QIODevice::Text))
        this->p_fileOut = new QTextStream(p_file);
    else
        this->consoleLog(ERROR, tr("Couldn't open file for log messages."));

}

SKYLOGGER::SkyLogger::~SkyLogger()
{
    delete p_fileOut;
    delete p_file;
}

void SKYLOGGER::SkyLogger::logMessage(SkyLoggerTypes type, const QString & message)
{
    this->consoleLog(type, message);
    this->fileLog(type, message);
}

void SKYLOGGER::SkyLogger::consoleLog(SkyLoggerTypes type, const QString & message)
{
    switch(type)
    {
    case INFO:
        qDebug() << PREFIX << "\tINFO\t" << message;
        break;

    case WARNING:
        qDebug() << PREFIX << "\tWARNING\t" << message;
        break;

    case ERROR:
        qDebug() << PREFIX << "\tERROR\t" << message;
        break;

    case DEBUG:
        qDebug() << PREFIX << "\tDEBUG\t" << message;
        break;

    case VERBOSE:
        qDebug() << PREFIX << "\tVERBOSE\t" << message;
        break;

    }
}

void SKYLOGGER::SkyLogger::fileLog(SkyLoggerTypes type, const QString & message)
{
    if(p_fileOut->status() ==  QTextStream::Ok)
    {
        switch(type)
        {
        case INFO:
            *p_fileOut << PREFIX << "\tINFO\t" << message << endl;
            break;

        case WARNING:
            *p_fileOut << PREFIX << "\tWARNING\t" << message << endl;
            break;

        case ERROR:
            *p_fileOut << PREFIX << "\tERROR\t" << message << endl;
            break;

        case DEBUG:
            *p_fileOut << PREFIX << "\tDEBUG\t" << message << endl;
            break;

        case VERBOSE:
            *p_fileOut << PREFIX << "\tVERBOSE\t" << message << endl;
            break;

        }
    }
    else
    {
        this->consoleLog(ERROR, QString(tr("Couldn't write log message in log file.")));
    }
}
