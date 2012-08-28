#ifndef SKYEXTERNALDEVICE_H
#define SKYEXTERNALDEVICE_H

#include <skycomponent.h>
#include "ExternalDeviceImpl/starpointercommunication.h"

#include <QTimer>

#define UPDATEINTERVALL 3000

class SkyExternalDevice : public SkyComponent
{
    Q_OBJECT
public:
    SkyExternalDevice(SkyConfiguration* config, QObject *parent = 0);
    ~SkyExternalDevice();

signals:
    void newData(double longitude, double latitude,
                 int accXComp, int accYComp, int accZComp,
                 int magXComp, int magYComp, int magZComp);

public slots:
    virtual void start();
    virtual void stop();

private slots:
    void handleReceivedGPSData(double longitude, double latitude);
    void handleReceivedAccelormeterData(int,int,int);
    void handleReceivedMagnetometerData(int,int,int);

    void handleLogError(QString message);
    void handleLogInfo(QString message);
    void handleLogVerbose(QString message);

    void timerTimeout();

private:
    ExternalDeviceImpl::StarPointerCommunication* m_com;
    QTimer* m_timer;

    double m_longitude;
    double m_latitude;
    int m_accXComp;
    int m_accYComp;
    int m_accZComp;
    int m_magXComp;
    int m_magYComp;
    int m_magZComp;

    double m_longitude_lastSent;
    double m_latitude_lastSent;
    int m_accXComp_lastSent;
    int m_accYComp_lastSent;
    int m_accZComp_lastSent;
    int m_magXComp_lastSent;
    int m_magYComp_lastSent;
    int m_magZComp_lastSent;
};

#endif // SKYEXTERNALDEVICE_H
