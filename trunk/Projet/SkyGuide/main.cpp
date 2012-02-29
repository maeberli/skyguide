#include <QtCore/QCoreApplication>

#include "skycore.h"

//todo: maybe remove the following comment
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SkyCore *tmp = new SkyCore();

    QTimer::singleShot(2000, &a, SLOT(quit())); //stop after 5 seconds

    return a.exec();
}
