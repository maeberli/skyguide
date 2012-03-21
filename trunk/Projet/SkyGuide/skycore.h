#ifndef SKYCORE_H
#define SKYCORE_H

#include <QObject>

#include <skycomponent.h>
#include <skydatabase.h>
#include <skylogger.h>
#include <skycalculator.h>
#include <skyexternaldevice.h>
#include <skygui.h>

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
    void handleReceivedDirectinoData(int direction);
    void handleReceivedPositionData(int position);
    void handleReceivedOrientationData(int slope, int inclLeftRigth);

private:
    SKYLOGGER::SkyLogger* p_logger;
    SkyDatabase* p_database;
    SkyCalculator* p_calculator;
    SkyExternalDevice* p_externalDevice;
    SkyGui* p_gui;

};

#endif // SKYCORE_H
