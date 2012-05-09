#ifndef SKYCORE_H
#define SKYCORE_H

#include <QObject>

#include <skycomponent.h>
#include <skydatabase.h>
#include <skylogger.h>
#include <skycalculator.h>
#include <skyexternaldevice.h>
#include <skygui.h>
#include <skyextdevdatahandler.h>

class SkyCore : SkyComponent
{
    Q_OBJECT
public:
    explicit SkyCore(QObject *parent = 0);
    ~SkyCore();

public slots:
    virtual void start();
    virtual void stop();

private slots:
    void calculateRange(int slope, int inclLeftRight, int direction, int positionData);

private:
    SKYLOGGER::SkyLogger* p_logger;
    SkyConfiguration* p_config;
    SkyDatabase* p_database;
    SkyCalculator* p_calculator;
    SkyExternalDevice* p_externalDevice;
    SkyGui* p_gui;
    SkyExtDevDataHandler* p_extDevDataHandler;

};

#endif // SKYCORE_H
