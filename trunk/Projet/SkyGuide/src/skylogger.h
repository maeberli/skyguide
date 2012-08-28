#ifndef SKYLOGGER_H
#define SKYLOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "skyloggertypes.h"

namespace SKYLOGGER
{

class SkyLogger : public QObject
{
    Q_OBJECT
public:
    explicit SkyLogger(QObject *parent = 0);
    ~SkyLogger();

signals:
    void receivedError(const QString & message);
    void receivedWarning(const QString & message);
    void receivedInfo(const QString & message);

public slots:
    void logMessage(SKYLOGGER::SkyLoggerTypes type, const QString & message);

private:
    void consoleLog(SKYLOGGER::SkyLoggerTypes type, const QString & message);
    void fileLog(SKYLOGGER::SkyLoggerTypes type, const QString & message);
    void emitSignals(SKYLOGGER::SkyLoggerTypes type, const QString & message);

    QFile* p_file;
    QTextStream* p_fileOut;
};

}


#endif // SKYLOGGER_H
