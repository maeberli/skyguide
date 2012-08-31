/**
  * Class declaration file of SkyExternalDevice.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYEXTERNALDEVICE_H
#define SKYEXTERNALDEVICE_H

//include Qt-headers
#include <QTimer>

//include SkyGuide specific headers
#include "skycomponent.h"
#include "ExternalDeviceImpl/starpointercommunication.h"

#define UPDATEINTERVALL 3000  //< intervall of checking for new data from the external device.

/**
  * This class adapts the interface the comminucation implementation to the SkyCore expected interface.
  *
  * This class inherits from the SkyComponent to provide some standardized methodes.
  */
class SkyExternalDevice : public SkyComponent
{
    Q_OBJECT
public:
    /**
      * Constructur, creates object.
      *
      * @param config   constant pointer to a config object, which a component could use.
      * @param parent   parent object (Qt-specific)
      */
    SkyExternalDevice(SkyConfiguration* config, QObject *parent = 0);

    /**
      * Destructor, cleanup.
      */
    ~SkyExternalDevice();

signals:
    /**
      * Signals that a new data set from the external device is arrived.
      *
      * @param longitude    gps longitude information.
      * @param latitude     gps latitude information.
      * @param accXComp     x component of the accelormeter vector.
      * @param accYComp     y component of the accelormeter vector.
      * @param accZComp     z component of the accelormeter vector.
      * @param magXComp     x component of the magnetometer vector.
      * @param magYComp     y component of the magnetometer vector.
      * @param magZComp     z component of the magnetometer vector.
      */
    void newData(double longitude, double latitude,
                 int accXComp, int accYComp, int accZComp,
                 int magXComp, int magYComp, int magZComp);

public slots:
    /**
      * Starts the communaction with the external device.
      *
      * At the same time the timer for new data checks will be startet.
      */
    void start();

    /**
      * stops the communication with the external device.
      *
      * At the same time the timer for new data checks will be stoped.
      */
    void stop();

private slots:

    /**
      * Stores GPS data.
      *
      * @param longitude    gps longitude to store.
      * @param latitude     gps latitude to store.
      */
    void handleReceivedGPSData(double longitude, double latitude);

    /**
      * Stores accelormeter data.
      *
      * @param xComp        x component of the accelormeter vector.
      * @param yComp        y component of the accelormeter vector.
      * @param zComp        z component of the accelormeter vector.
      */
    void handleReceivedAccelormeterData(int xComp, int yComp, int zComp);

    /**
      * Stores magnetometer data.
      *
      * @param xComp        x component of the magnetometer vector.
      * @param yComp        y component of the magnetometer vector.
      * @param zComp        z component of the magnetometer vector.
      */
    void handleReceivedMagnetometerData(int xComp, int yComp, int zComp);

    /**
      * Methode to log an error message.
      *
      * This methode uses the logMessage signal of the SkyComponent baseclass.
      *
      * @param message      message-text to log.
      */
    void handleLogError(QString message);

    /**
      * Methode to log an Info message.
      *
      * This methode uses the logMessage signal of the SkyComponent baseclass.
      *
      * @param message      message-text to log.
      */
    void handleLogInfo(QString message);

    /**
      * Methode to log a verbose message.
      *
      * This methode uses the logMessage signal of the SkyComponent baseclass.
      *
      * @param message      message-text to log.
      */
    void handleLogVerbose(QString message);

    /**
      * checks if a new data set is available and emit the signal if necessary.
      */
    void checkNewDataAvailable();

private:
    ExternalDeviceImpl::StarPointerCommunication* m_com;
    QTimer* m_timer;

    double m_longitude;             //< actual gps longitude information
    double m_latitude;              //< actual gps latitude information
    int m_accXComp;                 //< actual accelormeter vector x component
    int m_accYComp;                 //< actual accelormeter vector y component
    int m_accZComp;                 //< actual accelormeter vector z component
    int m_magXComp;                 //< actual magnetometer vector x component
    int m_magYComp;                 //< actual magnetometer vector y component
    int m_magZComp;                 //< actual magnetometer vector z component

    double m_longitude_lastSent;    //< last distributed gps longitude information
    double m_latitude_lastSent;     //< last distributed gps latitude information
    int m_accXComp_lastSent;        //< last distributed accelormeter vector x component
    int m_accYComp_lastSent;        //< last distributed accelormeter vector y component
    int m_accZComp_lastSent;        //< last distributed accelormeter vector z component
    int m_magXComp_lastSent;        //< last distributed magnetometer vector x component
    int m_magYComp_lastSent;        //< last distributed magnetometer vector y component
    int m_magZComp_lastSent;        //< last distributed magnetometer vector z component
};

#endif // SKYEXTERNALDEVICE_H
