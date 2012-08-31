/**
  * Class declaration file of SkyLogger
  *
  * \author Marco Aeberli
  *
  * \copyright Project P1 group DLM14 2012, all rights reserved
  */

#ifndef SKYLOGGER_H
#define SKYLOGGER_H

//include Qt-headers
#include <QObject>
#include <QFile>
#include <QTextStream>

//include SkyGuide specific headers
#include "skyloggertypes.h"

namespace SKYLOGGER
{

/**
  * Class SkyLogger implements the fonctionality for logging information on console and in file.
  */
class SkyLogger : public QObject
{
    Q_OBJECT
public:
    /**
      * Base constructor. Initialize the object.
      *
      * @param parent   parent object.
      */
    explicit SkyLogger(QObject *parent = 0);

    /**
      * Destructor, do the clean up.
      */
    ~SkyLogger();

signals:
    /**
      * Signal should be emited when object of SkyLogger has to log a message of type ERROR.
      *
      * @param message  received error message.
      */
    void receivedError(const QString& message);

    /**
      * Signal should be emited when object of SkyLogger has to log a message of type WARNING.
      *
      * @param message  received warning message.
      */
    void receivedWarning(const QString& message);

    /**
      * Signal should be emited when object of SkylOgger has to log a message of type INFO.
      *
      * @param message  received info message.
      */
    void receivedInfo(const QString& message);

public slots:
    /**
      * Methode which handels the logging of a message, diferenced by type.
      *
      * @param type     Defines the type of the message to log.
      * @param message  Message text to log.
      */
    void logMessage(SKYLOGGER::SkyLoggerTypes type, const QString& message);

private:
    /**
      * Methode writes a log message to the console.
      *
      * @param type     Defines the type of the message to log.
      * @param message  Message text to log.
      */
    void consoleLog(SKYLOGGER::SkyLoggerTypes type, const QString& message);

    /**
      * Methode writes a log message to a logfile.
      *
      * @param type     Defines the type of the message to log.
      * @param message  Message text to log.
      */
    void fileLog(SKYLOGGER::SkyLoggerTypes type, const QString& message);

    /**
      * Methode emits the to the type associeted signal if neccessaire.
      *
      * @param type     Defines the type of the log message.
      * @param message  Message text to log.
      */
    void emitSignals(SKYLOGGER::SkyLoggerTypes type, const QString& message);

    QFile* p_file;          //< log file object.
    QTextStream* p_fileOut; //< textstream object to write to the log file.
};

}


#endif // SKYLOGGER_H
