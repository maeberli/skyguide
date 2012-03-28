#include "skycore.h"

using namespace SKYLOGGER;

SkyCore::SkyCore(QObject *parent) :
    SkyComponent(parent)
{
    p_logger = new SkyLogger(this);
    p_database = new SkyDatabase(this);
    p_calculator = new SkyCalculator(this);
    p_externalDevice = new SkyExternalDevice(this);
    p_gui = new SkyGui(this);
    p_extDevDataHandler = new SkyExtDevDataHandler(this);

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
    connect(p_externalDevice, SIGNAL(receivedDirectionData(int)),
            p_extDevDataHandler, SLOT(setDirectionData(int)));
    connect(p_externalDevice, SIGNAL(receivedOrientationData(int,int)),
            p_extDevDataHandler, SLOT(setOrientationData(int,int)));
    connect(p_externalDevice, SIGNAL(receivedPositionData(int)),
            p_extDevDataHandler, SLOT(setPositionData(int)));
    connect(p_extDevDataHandler, SIGNAL(newExtDataAvailable(QList<SkyGuiElement*>)),
            p_gui, SLOT(updateAffichage(QList<SkyGuiElement*>)));

}

SkyCore::~SkyCore()
{
    delete p_database;
    delete p_calculator;
    delete p_externalDevice;
    delete p_gui;

    //delete logger as last element.
    delete p_logger;
}

void SkyCore::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Start SkyCore -> not implemented"));
}

void SkyCore::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Stop SkyCore -> not implemented"));
}
