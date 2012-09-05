/**
  * Class implementation file of SkyGui.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include <QObject>

#include "skygui.h"
#include "GuiImpl/mainwindow.h"
#include "GuiImpl/skystarfield.h"

SkyGui::SkyGui(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyGui"));

    p_win = new MainWindow();

    QObject::connect(this, SIGNAL(startRepaintSky(QList<SkyGuiElement *> *,double,double)), p_win, SLOT(repaintSky(QList<SkyGuiElement *> *,double,double)));
    connect(p_win, SIGNAL(sendStartAffichage()),
            this, SLOT(receiveStartAffichage()));
    connect(p_win, SIGNAL(sendStopAffichage()),
            this, SLOT(receiveStopAffichage()));
}

SkyGui::~SkyGui()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Deconstructor SkyGui"));
    delete p_win;
}

void SkyGui::showWindow()
{
    p_win->show();
}

void SkyGui::showWarning(const QString &message)
{
    p_win->appendLogMessage("Warning: " + message);
}

void SkyGui::showError(const QString &message)
{
    p_win->appendLogMessage("Error: " + message);
}

void SkyGui::showInfo(const QString &message)
{
    p_win->appendLogMessage("Info: " + message);
}

void SkyGui::updateAffichage(QList<SkyGuiElement*> *elements, double xP, double yP)
{
    emit startRepaintSky(elements, xP, yP);
}

void SkyGui::receiveStartAffichage()
{
    emit startAffichage();
}

void SkyGui::receiveStopAffichage()
{
    emit stopAffichage();
}
