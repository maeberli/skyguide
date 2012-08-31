/**
  * Class implementation file of SkyLogger
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "skylogger.h"

#include <QDebug>
#include <QTime>
#include <QtCore/QCoreApplication>

#define PREFIX QTime::currentTime().toString("hh:mm:ss.zzz")    //< Base prefix for logging message to console, file, etc. ...
#define FILENAME "SkyGuide.log"


SKYLOGGER::SkyLogger::SkyLogger(QObject *parent) :
    QObject(parent)
{
    //open/create the file to log.
    this->p_file = new QFile(QCoreApplication::applicationDirPath()+"/"+FILENAME);

    if(p_file->open(QIODevice::Append |  QIODevice::Text))
    {
        this->p_fileOut = new QTextStream(p_file);
    }
    else // possible if no rights, no space left, ...
    {
        this->consoleLog(ERROR, tr("Couldn't open file for log messages."));
    }

}

SKYLOGGER::SkyLogger::~SkyLogger()
{
    delete p_fileOut;
    delete p_file;
}

void SKYLOGGER::SkyLogger::logMessage(SKYLOGGER::SkyLoggerTypes type, const QString& message)
{
    this->consoleLog(type, message);
    this->fileLog(type, message);
    this->emitSignals(type, message);
}

void SKYLOGGER::SkyLogger::consoleLog(SKYLOGGER::SkyLoggerTypes type, const QString& message)
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

void SKYLOGGER::SkyLogger::fileLog(SKYLOGGER::SkyLoggerTypes type, const QString& message)
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

void SKYLOGGER::SkyLogger::emitSignals(SKYLOGGER::SkyLoggerTypes type, const QString& message)
{
    switch(type)
    {
    case SKYLOGGER::ERROR:
        emit receivedError(message);
        break;
    case SKYLOGGER::INFO:
        emit receivedInfo(message);
        break;
    case SKYLOGGER::WARNING:
        emit receivedWarning(message);
        break;
    case SKYLOGGER::VERBOSE:
    case SKYLOGGER::DEBUG:
    default:
        break;
    }
}
