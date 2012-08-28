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
    m_magZComp(0),
    m_longitude_lastSent(0.0),
    m_latitude_lastSent(0.0),
    m_accXComp_lastSent(0),
    m_accYComp_lastSent(0),
    m_accZComp_lastSent(0),
    m_magXComp_lastSent(0),
    m_magYComp_lastSent(0),
    m_magZComp_lastSent(0)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyExternalDevice"));

    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()),
              this, SLOT(timerTimeout()));

    m_com = new StarPointerCommunication(
                p_config->getConfItem("comPort", "/dev/ttyUSB0").toString(),
                (AbstractSerial::BaudRate)p_config->getConfItem("baudrate", AbstractSerial::BaudRate9600).toInt(),
                (AbstractSerial::Parity)p_config->getConfItem("parity", AbstractSerial::ParityNone).toInt(),
                (AbstractSerial::DataBits)p_config->getConfItem("databits", AbstractSerial::DataBits8).toInt(),
                (AbstractSerial::Flow)p_config->getConfItem("flow", AbstractSerial::FlowControlOff).toInt(),
                this
                );

    connect(m_com, SIGNAL(receivedGPSData(double,double)),
            this, SLOT(handleReceivedGPSData(double,double)));
    connect(m_com, SIGNAL(receivedAccelormeterData(int,int,int)),
            this, SLOT(handleReceivedAccelormeterData(int,int,int)));
    connect(m_com, SIGNAL(receivedMagnetometerData(int,int,int)),
            this, SLOT(handleReceivedMagnetometerData(int,int,int)));
    connect(m_com, SIGNAL(logInfo(QString)),
            this, SLOT(handleLogInfo(QString)));
    connect(m_com, SIGNAL(logVerbose(QString)),
            this, SLOT(handleLogVerbose(QString)));
    connect(m_com, SIGNAL(logError(QString)),
            this, SLOT(handleLogError(QString)));
}

SkyExternalDevice::~SkyExternalDevice()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Destructor SkyExternalDevice"));
    delete m_com;
    delete m_timer;
}

void SkyExternalDevice::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("start SkyExternalDevice"));

    m_com->openConnection();
    m_timer->start(UPDATEINTERVALL);
}

void SkyExternalDevice::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("stop SkyExternalDevice"));

    m_com->closeConnection();
    m_timer->stop();
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

void SkyExternalDevice::handleLogError(QString message)
{
    emit logMessage(SKYLOGGER::ERROR, message);
}

void SkyExternalDevice::handleLogInfo(QString message)
{
    emit logMessage(SKYLOGGER::INFO, message);
}

void SkyExternalDevice::handleLogVerbose(QString message)
{
    emit logMessage(SKYLOGGER::VERBOSE, message);
}

void SkyExternalDevice::timerTimeout()
{
    if( m_longitude_lastSent != m_longitude
            || m_latitude_lastSent != m_latitude
            || m_accXComp_lastSent != m_accXComp
            || m_accYComp_lastSent != m_accYComp
            || m_accZComp_lastSent != m_accZComp
            || m_magXComp_lastSent != m_magXComp
            || m_magYComp_lastSent != m_magYComp
            || m_magZComp_lastSent != m_magZComp)
    {
        m_longitude_lastSent = m_longitude;
        m_latitude_lastSent = m_latitude;
        m_accXComp_lastSent = m_accXComp;
        m_accYComp_lastSent = m_accYComp;
        m_accZComp_lastSent = m_accZComp;
        m_magXComp_lastSent = m_magXComp;
        m_magYComp_lastSent = m_magYComp;
        m_magZComp_lastSent = m_magZComp;

        emit newData(m_longitude, m_latitude,
                     m_accXComp, m_accYComp, m_accZComp,
                     m_magXComp, m_magYComp, m_magZComp);
    }
}
