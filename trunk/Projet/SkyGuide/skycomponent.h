#ifndef SKYCOMPONENT_H
#define SKYCOMPONENT_H

#include <QObject>

#include <skyloggertypes.h>


class SkyComponent : public QObject
{
    Q_OBJECT
public:
    SkyComponent(QObject *parent = 0);

signals:
    void logMessage(SKYLOGGER::SkyLoggerTypes type, const QString & message);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

};

#endif // SKYCOMPONENT_H
