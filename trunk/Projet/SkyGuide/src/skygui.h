#ifndef SKYGUI_H
#define SKYGUI_H

#include <skycomponent.h>
#include <skyguielement.h>
#include <QList>
#include "GuiImpl/mainwindow.h"
#include "GuiImpl/skystarfield.h"
#include "skyguielement.h"

class SkyGui : public SkyComponent
{
    Q_OBJECT
public:
    SkyGui(SkyConfiguration* config, QObject *parent = 0);
    ~SkyGui();
    void showWindow();

signals:
    void startAffichage();
    void stopAffichage();

    void startRepaintSky(QList<SkyGuiElement *> *stars, double xP, double yP);

public slots:
    void start() { }
    void stop() { }

    void showWarning(const QString & message);
    void showError(const QString & message);
    void showInfo(const QString & message);
    void updateAffichage(QList<SkyGuiElement *> *elements, double xP, double yP);

private slots:
    void receiveStartAffichage();
    void receiveStopAffichage();

private:
    MainWindow *p_win;
};

#endif // SKYGUI_H
