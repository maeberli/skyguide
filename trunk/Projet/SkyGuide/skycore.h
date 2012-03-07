#ifndef SKYCORE_H
#define SKYCORE_H

#include <QObject>

#include <skydatabase.h>
#include <skylogger.h>
#include <skycalculator.h>
#include <skyexternaldevice.h>

class SkyCore : public QObject
{
    Q_OBJECT
public:
    explicit SkyCore(QObject *parent = 0);
    ~SkyCore();

signals:

public slots:

private:
    SKYLOGGER::SkyLogger* p_logger;
    SkyDatabase* p_database;
    SkyCalculator* p_calculator;
    SkyExternalDevice* p_externalDevice;

};

#endif // SKYCORE_H
