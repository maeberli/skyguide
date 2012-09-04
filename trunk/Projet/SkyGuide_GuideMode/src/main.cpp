#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QTimer>

#include <cmath>
#include <iostream>

#include "applicationcontroler.h"

void showHelp();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //check if minimal argument count is available
    if(a.arguments().count() < 4)
    {
        showHelp();
    }
    else
    {
        //necessaire parameters
        double azimuth = a.arguments().at(1).toDouble() * (M_PI / 180);
        double altitude = a.arguments().at(2).toDouble() * (M_PI / 180);
        QString serialDevice = a.arguments().at(3);

        //optional parameters
        int flashUpdateIntervall = 400;
        double verbose = false;

        if(a.arguments().count() >= 4)
        {
            for(int i = 4; i < a.arguments().count(); ++i)
            {
                if(a.arguments().at(i) == "-V") { verbose = true; }
                else if(a.arguments().at(i) == "-i") { flashUpdateIntervall = a.arguments().at(++i).toInt(); }
                else if(a.arguments().at(i) == "-h"){ showHelp(); }
                else if(a.arguments().at(i) == "-H"){ showHelp(); }
                else
                    showHelp();
            }
        }

        GuideModeHandler handler(azimuth,
                                 altitude,
                                 serialDevice,
                                 flashUpdateIntervall,
                                 verbose);

        TerminationHandler termHandler(&handler);

        // Quit the application if the applicationControler Thread has finished.scheiss
        QObject::connect(&termHandler, SIGNAL(started()),
                         &handler, SLOT(startupCommunication()));
        QObject::connect(&termHandler, SIGNAL(finished()),
                         &a, SLOT(quit()));

        //Initialize the communcation connection.
        termHandler.start();

        int rv = a.exec();

        return rv;
    }
}

void showHelp()
{
    std::cout << "Usage: SkyGuide_GuideMode AZIMUTH ALTITUDE DEVICENAME [OPTION...]" << std::endl << std::endl
              << "AZIMUTH    asdfjlasdf" << std::endl
              << "ALTITUDE   asdfjlasdf" << std::endl
              << "DEVICENAME asdfjlasdf" << std::endl << std::endl
              << "-h, -H,    show this help" << std::endl
              << "-V         show verbose output" << std::endl
              << "-i         Intervall for flash update in milliseconds (default 400 msec)" << std::endl;

    exit(-1);
}
