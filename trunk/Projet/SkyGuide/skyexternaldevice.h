#ifndef SKYEXTERNALDEVICE_H
#define SKYEXTERNALDEVICE_H

#include <skycomponent.h>

class SkyExternalDevice : public SkyComponent
{
public:
    SkyExternalDevice(QObject *parent = 0);
    ~SkyExternalDevice();

signals:
    void receivedOrientationData(int slope, int inclLeftRight);
    void receivedDirectionData(int direction);
    void receivedPositionData(int positionData);

public slots:
    virtual void start();
    virtual void stop();
};

#endif // SKYEXTERNALDEVICE_H
