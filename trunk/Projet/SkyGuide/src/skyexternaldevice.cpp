#include "skyexternaldevice.h"

using namespace ExternalDeviceImpl;

SkyExternalDevice::SkyExternalDevice(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent),
    m_longitude(""),
    m_longSide('N'),
    m_latitude(""),
    m_latSide('E'),
    m_accXComp(0),
    m_accYComp(0),
    m_accZComp(0),
    m_magXComp(0),
    m_magYComp(0),
    m_magZComp(0)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyExternalDevice"));

    m_com = new StarPointerCommunication();
    m_timer = new QTimer(this);


    connect(m_com, SIGNAL(receivedGPSData(QString,char,QString,char)),
            this, SLOT(handleReceivedGPSData(QString,char,QString,char)));
    connect(m_com, SIGNAL(receivedAccelormeterData(int,int,int)),
            this, SLOT(handleReceivedAccelormeterData(int,int,int)));
    connect(m_com, SIGNAL(receivedMagnetometerData(int,int,int)),
            this, SLOT(handleReceivedMagnetometerData(int,int,int)));

    connect(m_timer, SIGNAL(timeout()),
              this, SLOT(timerTimeout()));
    m_timer->start(UPDATEINTERVALL);
}

SkyExternalDevice::~SkyExternalDevice()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Destructor SkyExternalDevice"));
    delete m_com;
    delete m_timer;
}

void SkyExternalDevice::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("start SkyExternalDevice -> not implemented"));
}

void SkyExternalDevice::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("stop SkyExternalDevice -> not implemented"));
}

void SkyExternalDevice::handleReceivedGPSData(QString longitude, char longSide, QString latitude, char latSide)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("received GPS DATA(%1;%2;%3;%4)").arg(longitude).arg(longSide).arg(latitude).arg(latSide));
    m_longitude = longitude;
    m_longSide = longSide;
    m_latitude = latitude;
    m_latSide = latSide;
}

void SkyExternalDevice::handleReceivedAccelormeterData(int xComp, int yComp, int zComp)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("received Accelormeter Data(%1;%2;%3)").arg(xComp).arg(yComp).arg(zComp));
    m_accXComp = xComp;
    m_accYComp = yComp;
    m_accZComp = zComp;
}

void SkyExternalDevice::handleReceivedMagnetometerData(int xComp, int yComp, int zComp)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("received Magnetometer Data(%1;%2;%3)").arg(xComp).arg(yComp).arg(zComp));
    m_magXComp = xComp;
    m_magYComp = yComp;
    m_magZComp = zComp;
}

void SkyExternalDevice::timerTimeout()
{
    emit newData(m_longitude, m_longSide, m_latitude, m_latSide,
                 m_accXComp, m_accYComp, m_accZComp,
                 m_magXComp, m_magYComp, m_magZComp);
}
