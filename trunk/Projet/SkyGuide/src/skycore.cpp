#include <QList>

#include "skycore.h"
#include "skyposition.h"
#include "skytransformation.h"

using namespace SKYLOGGER;

SkyCore::SkyCore(QObject *parent) :
    SkyComponent(p_config, parent)
{
    p_logger = new SkyLogger(this);
    p_config = new SkyConfiguration(this);
    p_database = new SkyDatabase(p_config, this);
    p_calc = new SkyCalculator(p_config, this);
    p_externalDevice = new SkyExternalDevice(p_config, this);
    p_gui = new SkyGui(p_config, this);

    // connect logging slots of each component with signal of logger
    connect(this, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
    connect(p_database, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
            p_logger, SLOT(logMessage(SKYLOGGER::SkyLoggerTypes,QString)));
    connect(p_calc, SIGNAL(logMessage(SKYLOGGER::SkyLoggerTypes,QString)),
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
            p_calc, SLOT(start()));
    connect(p_gui, SIGNAL(stopAffichage()),
            p_calc, SLOT(stop()));

    connect(p_gui, SIGNAL(startAffichage()),
            p_externalDevice, SLOT(start()));
    connect(p_gui, SIGNAL(stopAffichage()),
            p_externalDevice, SLOT(stop()));

    //connect the signals for the received informations of the externalDevice object
    //to the local slots
    connect(p_externalDevice, SIGNAL(newData(double,double,int,int,int,int,int,int)),
            this, SLOT(calculateRange(double,double,int,int,int,int,int,int)));

}

SkyCore::~SkyCore()
{
    delete p_database;
    delete p_calc;
    delete p_externalDevice;
    delete p_gui;

    delete p_config;

    //delete logger as last element.
    delete p_logger;

    int count = 0;
    allStars->count();
    for (int i = 0; i < count; ++i)
        delete allStars->at(i);
    delete allStars;
    count = guiList->count();
    for (int i = 0; i < count; ++i)
        delete guiList->at(i);
    delete guiList;
}

void SkyCore::startGui()
{
    p_gui->showWindow();

    allStars = p_database->getSkyElements();

    int count = allStars->count();

    // Transformation (site bleu) + projection (x et y)
    SkyPosition *here = new SkyPosition(46.992181, 6.915894);

    guiList = new QList<SkyGuiElement *>();

    double angle = SkyTransformation::getAngle();

    for (int i = 0; i < count; ++i)
        SkyTransformation::transformation(allStars->at(i), here, angle);

    delete here;

    double x = 0.0, y = 0.0;
    for (int i = 0; i < count; ++i)
    {
        if (allStars->at(i)->getHeight() > 0.0)
        {
            SkyTransformation::projection(allStars->at(i), &x, &y, 320);
            guiList->append(new SkyGuiElement(*(allStars->at(i)), x, y));
        }
    }

    SkyElement el(100,100,"jkl","asdfj",12.5,2);
    guiList->append(new SkyGuiElement(el,0,0));
    guiList->append(new SkyGuiElement(el,10,0));
    guiList->append(new SkyGuiElement(el,0,10));
    guiList->append(new SkyGuiElement(el,50,0));
    guiList->append(new SkyGuiElement(el,100,0));

    p_gui->updateAffichage(guiList);
}

void SkyCore::calculateRange(double longitude, double latitude,
                             int accXComp, int accYComp, int accZComp,
                             int magXComp, int magYComp, int magZComp)
{
    Vect3D vectAcc(accXComp, accYComp, accZComp);
    Vect3D vectMag(magXComp, magYComp, magZComp);

    vectAcc = p_calc->getUnitVector( vectAcc );
    vectMag = p_calc->getUnitVector( vectMag );

    //calculate vector north and east based on vector of magnetometer and accelerometer
    Vect3D east = p_calc->getUnitVector( p_calc->crossProduct(vectMag,vectAcc) );
    Vect3D north = p_calc->getUnitVector( p_calc->crossProduct(east,vectAcc) );

    Vect3D vectP(0,0,-1);

    //calculate inclination and right ascension of vector which points to the stars.
    double incl = p_calc->getAngleBetween(vectP,vectAcc) - M_PI/2;
    double compDir = p_calc->getCompassDirection(vectP, north, east);
    double azimut = p_calc->transformCompDirectionSystem(compDir);

    emit logMessage(SKYLOGGER::INFO, tr("Current pointer inclination: %1").arg(incl * (180/M_PI)));
    emit logMessage(SKYLOGGER::INFO, tr("Current pointer compass: %1").arg(compDir * (180/M_PI)));
    emit logMessage(SKYLOGGER::INFO, tr("Current pointer azimut: %1").arg(azimut * (180/M_PI)));
}

void SkyCore::start()
{
}

void SkyCore::stop()
{
}
