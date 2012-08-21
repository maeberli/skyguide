#include "skycore.h"

using namespace SKYLOGGER;

QDebug operator<<(QDebug dbg, const Vect3D& v)
{
    dbg << "(" << v.x << "," << v.y << "," << v.z << ")";
    return dbg;
}

SkyCore::SkyCore(QObject *parent) :
    SkyComponent(p_config, parent)
{
    p_logger = new SkyLogger(this);
    p_config = new SkyConfiguration(this);
    p_database = new SkyDatabase(p_config, this);
    p_calculator = new SkyCalculator(p_config, this);
    p_externalDevice = new SkyExternalDevice(p_config, this);
    p_gui = new SkyGui(p_config, this);

    // connect logging slots of each component with signal of logger
    connect(this, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
    connect(p_database, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
    connect(p_calculator, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
    connect(p_externalDevice, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
    connect(p_gui, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));

    //connect logger signals with gui slots
    connect(p_logger, SIGNAL(receivedError(QString)),
            p_gui, SLOT(showError(QString)));
    connect(p_logger, SIGNAL(receivedWarning(QString)),
            p_gui, SLOT(showWarning(QString)));
    connect(p_logger, SIGNAL(receivedInfo(QString)),
            p_gui, SLOT(showInfo(QString)));

    //connect start signal of gui with each components start/stop slot
    connect(p_gui, SIGNAL(startAffichage()),
            this, SLOT(start()));
    connect(p_gui, SIGNAL(stopAffichage()),
            this, SLOT(stop()));

    connect(p_gui, SIGNAL(startAffichage()),
            p_database, SLOT(start()));
    connect(p_gui, SIGNAL(stopAffichage()),
            p_database, SLOT(stop()));

    connect(p_gui, SIGNAL(startAffichage()),
            p_calculator, SLOT(start()));
    connect(p_gui, SIGNAL(stopAffichage()),
            p_calculator, SLOT(stop()));

    connect(p_gui, SIGNAL(startAffichage()),
            p_externalDevice, SLOT(start()));
    connect(p_gui, SIGNAL(stopAffichage()),
            p_externalDevice, SLOT(stop()));

    //connect the signals for the received informations of the externalDevice object
    //to the local slots
    connect(p_externalDevice, SIGNAL(newData(QString,char,QString,char,int,int,int,int,int,int)),
            this, SLOT(calculateRange(QString,char,QString,char,int,int,int,int,int,int)));

}

SkyCore::~SkyCore()
{
    delete p_database;
    delete p_calculator;
    delete p_externalDevice;
    delete p_gui;

    delete p_config;

    //delete logger as last element.
    delete p_logger;
}

void SkyCore::startGui()
{
    // pour tester l'affichage
    // p_gui->updateAffichage();
    p_gui->showWindow();
}

void SkyCore::calculateRange(QString longitude, char longSide, QString latitude, char latSide,
                             int accXComp, int accYComp, int accZComp,
                             int magXComp, int magYComp, int magZComp)
{
    Vect3D vectAcc;
    vectAcc.x = accXComp;
    vectAcc.y = accYComp;
    vectAcc.z = accZComp;

    Vect3D vectMag;
    vectMag.x = magXComp;
    vectMag.y = magYComp;
    vectMag.z = magZComp;

    vectAcc = getUnitVector( vectAcc );
    vectMag = getUnitVector( vectMag );

    //calculate vector north and east based on vector of magnetometer and accelerometer
    Vect3D east = getUnitVector( crossProduct(vectMag,vectAcc) );
    Vect3D north = getUnitVector( crossProduct(east,vectAcc) );

    Vect3D vectP;
    vectP.x = 0;
    vectP.y = 0;
    vectP.z = -1;

    double incl = acos(scalarProduct(vectP,vectAcc) / (getNorm(vectP)*getNorm(vectAcc))) * (180/3.14159265)-90;
    double dir = atan2(scalarProduct(vectP,east), scalarProduct(vectP,north)) * (180/3.14159265)+180;
    qDebug() << "incl: " << incl;
    qDebug() << "dir:  " << dir;

}

void SkyCore::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Start SkyCore -> not implemented"));
}

void SkyCore::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Stop SkyCore -> not implemented"));
}
