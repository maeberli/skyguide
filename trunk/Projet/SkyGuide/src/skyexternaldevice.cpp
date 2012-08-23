#include "skyexternaldevice.h"

using namespace ExternalDeviceImpl;

SkyExternalDevice::SkyExternalDevice(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent),
    m_longitude(0.0),
    m_latitude(0.0),
    m_accXComp(0),
    m_accYComp(0),
    m_accZComp(0),
    m_magXComp(0),
    m_magYComp(0),
    m_magZComp(0)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyExternalDevice"));


//    AbstractSerial::BaudRate baudrate = (AbstractSerial::BaudRate)p_config->getConfItem("baudrate", AbstractSerial::BaudRate9600).toInt();
//    m_com = new StarPointerCommunication("/dev/ttyUSB0",AbstractSerial::BaudRate9600, AbstractSerial::ParityNone, AbstractSerial::DataBits8, AbstractSerial::FlowControlOff);

    m_com = new StarPointerCommunication(
                p_config->getConfItem("comPort", "/dev/ttyUSB0").toString(),
                (AbstractSerial::BaudRate)p_config->getConfItem("baudrate", AbstractSerial::BaudRate9600).toInt(),
                (AbstractSerial::Parity)p_config->getConfItem("parity", AbstractSerial::ParityNone).toInt(),
                (AbstractSerial::DataBits)p_config->getConfItem("databits", AbstractSerial::DataBits8).toInt(),
                (AbstractSerial::Flow)p_config->getConfItem("flow", AbstractSerial::FlowControlOff).toInt(),
                this
                );
    m_timer = new QTimer(this);


    connect(m_com, SIGNAL(receivedGPSData(double,double)),
            this, SLOT(handleReceivedGPSData(double,double)));
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

void SkyExternalDevice::handleReceivedGPSData(double longitude, double latitude)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("received GPS DATA(%1;%2)").arg(longitude).arg(latitude));
    m_longitude = longitude;
    m_latitude = latitude;
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
    emit newData(m_longitude, m_latitude,
                 m_accXComp, m_accYComp, m_accZComp,
                 m_magXComp, m_magYComp, m_magZComp);
}
