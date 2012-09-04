#include "guidemodehandler.h"

#include <QDebug>

GuideModeHandler::GuideModeHandler(
        double _refAzimuth,
        double _refAltitude,
        QString serialDevice,
        int flashUpdateIntervall,
        bool verboseOutput,
        QObject *parent)
    :QObject(parent),
      m_refAzimuth(_refAzimuth),
      m_refAltitude(_refAltitude),
      m_serialDevice(serialDevice),
      m_flashUpdateIntervall(flashUpdateIntervall),
      m_VERBOSEOUTPUT(verboseOutput),
      m_actAccCompX(0),
      m_actAccCompY(0),
      m_actAccCompZ(0),
      m_actMagCompX(0),
      m_actMagCompY(0),
      m_actMagCompZ(0),
      m_actLongitude(0.0),
      m_actLatitude(0.0)
{
    logVerbose("called constructor");

    m_calcTicker = new QTimer();

    m_com =  new StarPointerCommunication(
                m_serialDevice,
                "9600",
                "None",
                "8 bit",
                "Disable");

    connect(m_calcTicker, SIGNAL(timeout()),
            this, SLOT(sendNewDirection()));

    connect(m_com, SIGNAL(logError(QString)),
            this, SLOT(logError(QString)));
    connect(m_com, SIGNAL(logInfo(QString)),
            this, SLOT(logInfo(QString)));
    connect(m_com, SIGNAL(logVerbose(QString)),
            this, SLOT(logVerbose(QString)));

    connect(m_com, SIGNAL(receivedAccelormeterData(int,int,int)),
            this, SLOT(handleReceivedAccelormeterData(int,int,int)));
    connect(m_com, SIGNAL(receivedGPSData(double,double)),
            this, SLOT(handleReceivedGPSData(double,double)));
    connect(m_com, SIGNAL(receivedMagnetometerData(int,int,int)),
            this, SLOT(handleReceivedMagnetometerData(int,int,int)));
}

GuideModeHandler::~GuideModeHandler()
{
    logVerbose("called GuideModeHandler destructor");

    delete m_calcTicker;
    delete m_com;
}

void GuideModeHandler::startupCommunication()
{
    m_com->openConnection(StarPointerCommunication::ModeGuide);

    m_calcTicker->start(m_flashUpdateIntervall);
}

void GuideModeHandler::shutdownCommunication()
{
    m_calcTicker->stop();

    m_com->changeInModePointer();

    m_com->closeConnection();
}

void GuideModeHandler::logError(QString msg)
{
    qDebug() << "Error:\t" << msg;
}

void GuideModeHandler::logInfo(QString msg)
{
    qDebug() << "Info:\t" << msg;
}

void GuideModeHandler::logVerbose(QString msg)
{
    if(m_VERBOSEOUTPUT == true)
        qDebug() << "Verbose:\t" << msg;
}

void GuideModeHandler::handleReceivedAccelormeterData(int compX, int compY, int compZ)
{
    //logVerbose(tr("handleReceivedAccelormeterData(%1,%2,%3)").arg(compX).arg(compY).arg(compZ));
    m_actAccCompX = compX;
    m_actAccCompY = compY;
    m_actAccCompZ = compZ;
}

void GuideModeHandler::handleReceivedGPSData(double longitude, double latitude)
{
    //logVerbose(tr("handleReceivedGPSData((%1,%2)").arg(longitude).arg(latitude));
    m_actLongitude = longitude;
    m_actLatitude = latitude;
}

void GuideModeHandler::handleReceivedMagnetometerData(int compX,int compY,int compZ)
{
    //logVerbose(tr("handleReceivedMagnetometerData(%1,%2,%3)").arg(compX).arg(compY).arg(compZ));
    m_actMagCompX = compX;
    m_actMagCompY = compY;
    m_actMagCompZ = compZ;
}

void GuideModeHandler::sendNewDirection()
{
    Vect3D vectAcc(m_actAccCompX, m_actAccCompY, m_actAccCompZ);
    Vect3D vectMag(m_actMagCompX, m_actMagCompY, m_actMagCompZ);

    vectAcc = VectorOperations::getUnitVector( vectAcc );
    vectMag = VectorOperations::getUnitVector( vectMag );

    //calculate vector north and east based on vector of magnetometer and accelerometer
    Vect3D east = VectorOperations::getUnitVector( VectorOperations::crossProduct(vectMag,vectAcc) );
    Vect3D north = VectorOperations::getUnitVector( VectorOperations::crossProduct(east,vectAcc) );

    Vect3D vectP(0,0,-1);

    //calculate inclination and right ascension of vector which points to the stars.
    double altitude = VectorOperations::getAngleBetween(vectP,vectAcc) - M_PI/2;
    double compDir = VectorOperations::getCompassDirection(vectP, north, east);
    double azimuth = VectorOperations::transformCompDirectionSystem(compDir);

    logInfo(tr("Current pointer compDir: %1").arg(compDir * (180/M_PI)));
    logInfo(tr("Current pointer altitude: %1").arg(altitude * (180/M_PI)));
    logInfo(tr("Current pointer azimuth: %1").arg(azimuth * (180/M_PI)));

    Direction right_left =  Undef;
    Direction top_bottom = Undef;

    double azimuthMarge = 20*M_PI/180;
    double altitudeMarge = 20*M_PI/180;

    if(fabs(azimuth-m_refAzimuth) > azimuthMarge)
    {
        if(        (azimuth-m_refAzimuth < M_PI && m_refAzimuth-azimuth > -M_PI)
                || (azimuth-m_refAzimuth < -M_PI && m_refAzimuth-azimuth > M_PI)) // turn to west/left
            right_left = Left;
        else if(   (azimuth-m_refAzimuth > M_PI && m_refAzimuth-azimuth < -M_PI) // turn to east/right
                || (azimuth-m_refAzimuth > -M_PI && m_refAzimuth-azimuth < M_PI))
            right_left = Right;
    }

    if(m_refAltitude > (altitude + altitudeMarge)) // turn to top
        top_bottom = Top;
    else if(m_refAltitude < (altitude - altitudeMarge) ) // turn to bottom
        top_bottom = Bottom;

    Direction finalDirection = Undef;
    if(top_bottom == Undef && right_left == Undef)
    {
        finalDirection = Undef;
    }
    else if(top_bottom == Undef && right_left == Left)
    {
        finalDirection = Left;
    }
    else if(top_bottom == Undef && right_left == Right)
    {
        finalDirection = Right;
    }
    else if(top_bottom == Top && right_left == Undef)
    {
        finalDirection = Top;
    }
    else if(top_bottom == Top && right_left == Left)
    {
        finalDirection = TopLeft;
    }
    else if(top_bottom == Top && right_left == Right)
    {
        finalDirection = TopRight;
    }
    else if(top_bottom == Bottom && right_left == Undef)
    {
        finalDirection = Bottom;
    }
    else if(top_bottom == Bottom && right_left == Left)
    {
        finalDirection = BottomLeft;
    }
    else if(top_bottom == Bottom && right_left == Right)
    {
        finalDirection = BottomRight;
    }

    logInfo(tr("flash direction to: %1 %2")
            .arg(finalDirection)
            .arg(DirectionToString(finalDirection)));

    //correction of direction, based on the rotation of the card.
    if(finalDirection != Undef)
    {
        double rotAngle = atan2(vectAcc.y, vectAcc.x);
        rotAngle = (rotAngle < 0 ? rotAngle + (2*M_PI) : rotAngle) - (M_PI/2);

        int tmp = finalDirection + (int)(rotAngle / (M_PI/4));
        finalDirection = (Direction)(tmp%7);

        logInfo(tr("corrected flash direction to: %1 %2")
                .arg(finalDirection)
                .arg(DirectionToString(finalDirection)));
    }

    m_com->sendModeGuideFlash(finalDirection);
}
