/**
  * Class declaration file of SkyCore.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYCORE_H
#define SKYCORE_H

//include Qt-headers
#include <QObject>
#include <QList>

//include SkyGuide specific headers
#include <skycomponent.h>
#include <skydatabase.h>
#include <skylogger.h>
#include <skycalculator.h>
#include <skyexternaldevice.h>
#include <skygui.h>

/**
  * Core component of the application SkyGuide, which reunions all the components.
  */
class SkyCore : SkyComponent
{
    Q_OBJECT
public:
    /**
      * Consctructor, initalize an object
      *
      * @param parent   parent object (Qt-specific)
      */
    explicit SkyCore(QObject *parent = 0);

    /**
      * Destructor, cleanup.
      */
    ~SkyCore();

    void startGui();

public slots:
    /**
      * No functionality implemented. Not used for core component.
      */
    void start();


    /**
      * No functionality implemented. Not used for core component.
      */
    void stop();

private slots:
    /**
      * Calculates the actual pointet elements and sends the new elements to GUI.
      *
      * @param longitude    GPS longitude information.
      * @param latitude     GPS latitude information.
      * @param accXComp     X component of the accelerometer vector.
      * @param accYComp     Y component of the accelerometer vector.
      * @param accZComp     Z component of the accelerometer vector.
      * @param magXComp     X component of the magnetometer vector.
      * @param magYComp     Y component of the magnetometer vector.
      * @param magZComp     Z component of the magnetometer vector.
      */
    void calculateRange(double longitude, double latitude,
                        int accXComp, int accYComp, int accZComp,
                        int magXComp, int magYComp, int magZComp);


private:
    SKYLOGGER::SkyLogger* p_logger;         //< logger object.
    SkyConfiguration* p_config;             //< object contains the config(-fonctionality)
    SkyDatabase* p_database;                //< database component
    SkyCalculator* p_calc;                  //< calculation component
    SkyExternalDevice* p_externalDevice;    //< external device component
    SkyGui* p_gui;                          //< gui componet
    QList<SkyElement* >* allStars;
    QList<SkyGuiElement* >* guiList;

};

#endif // SKYCORE_H
