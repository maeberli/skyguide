#ifndef SKYCORE_H
#define SKYCORE_H

#include <QObject>
#include <QList>

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

    void startGui();

public slots:
    void start();
    void stop();

private slots:
    void calculateRange(double longitude, double latitude,
                        int accXComp, int accYComp, int accZComp,
                        int magXComp, int magYComp, int magZComp);


private:
    SKYLOGGER::SkyLogger* p_logger;
    SkyConfiguration* p_config;
    SkyDatabase* p_database;
    SkyCalculator* p_calc;
    SkyExternalDevice* p_externalDevice;
    SkyGui* p_gui;
    QList<SkyElement* >* allStars;
    QList<SkyGuiElement* >* guiList;

};

#endif // SKYCORE_H
