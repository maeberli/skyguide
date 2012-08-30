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
    if(a.arguments().count() < 3)
    {
        showHelp();
    }
    else
    {
        double azimuth = a.arguments().at(1).toDouble() * (M_PI / 180);
        double altitude = a.arguments().at(2).toDouble() * (M_PI / 180);
        double verbose = false;

        if(a.arguments().count() > 3)
        {
            for(int i = 3; i < a.arguments().count(); ++i)
            {
                if(a.arguments().at(i) == "-V") { verbose = true; }
                else if(a.arguments().at(i) == "-h"){ showHelp(); }
                else if(a.arguments().at(i) == "-H"){ showHelp(); }
                else
                    showHelp();
            }
        }

        ApplicationControler* appControl = new ApplicationControler(azimuth, altitude, verbose,&a);

        QObject::connect(appControl, SIGNAL(finished()),
                         &a, SLOT(quit()));

        QTimer::singleShot(0, appControl, SLOT(start()));

        return a.exec();
    }
}

void showHelp()
{
    std::cout << "Usage: SkyGuide_GuideMode AZIMUTH ALTITUDE [OPTION...]" << std::endl << std::endl
              << "-h, -H,    show this help" << std::endl
              << "-V         show verbose output" << std::endl;

    exit(-1);
}
