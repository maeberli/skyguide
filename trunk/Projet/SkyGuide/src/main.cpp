#include <QApplication>

#include "skycore.h"

//todo: maybe remove the following comment
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SkyCore *tmp = new SkyCore();
    tmp->startGui();

    return a.exec();
}
