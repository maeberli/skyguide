#ifndef SKYCOMPONENT_H
#define SKYCOMPONENT_H

#include <QObject>

#include <skyloggertypes.h>
#include <skyconfiguration.h>


class SkyComponent : public QObject
{
    Q_OBJECT
public:
    SkyComponent(SkyConfiguration* config, QObject *parent = 0);

signals:
    void logMessage(SKYLOGGER::SkyLoggerTypes type, const QString & message);

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    SkyConfiguration* p_config;

};

#endif // SKYCOMPONENT_H
