#ifndef SKYCORE_H
#define SKYCORE_H

#include <QObject>

#include <skydatabase.h>
#include <skylogger.h>
#include <skycalculator.h>
#include <skyexternaldevice.h>
#include <skygui.h>

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
    SkyGui* p_gui;

};

#endif // SKYCORE_H
