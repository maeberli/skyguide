#include <QApplication>

#include "mainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    mainWindow main;
    main.show();
    return app.exec();
}
