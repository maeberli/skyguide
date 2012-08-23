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
};

#endif // SKYEXTERNALDEVICE_H
