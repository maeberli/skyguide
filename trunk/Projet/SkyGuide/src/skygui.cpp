#include <QObject>
#include <QDebug>

#include "skygui.h"
#include "GuiImpl/mainwindow.h"
#include "GuiImpl/skystarfield.h"

SkyGui::SkyGui(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyGui"));

    p_win = new MainWindow();

    QObject::connect(this, SIGNAL(startRepaintSky(QList<SkyGuiElement *> *)), p_win, SLOT(repaintSky(QList<SkyGuiElement *> *)));
    QObject::connect(p_win, SIGNAL(sendStartAffichage()), this, SLOT(receiveStartAffichage()));
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

void SkyGui::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("start SkyGui -> not implemented"));
}

void SkyGui::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("stop SkyGui -> not implemented"));
}

void SkyGui::showWarning(const QString &message)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("showWarning slot SkyGui. Message: %1").arg(message));

}

void SkyGui::showError(const QString &message)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("showError slot SkyGui. Message: %1").arg(message));
}

void SkyGui::showInfo(const QString &message)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("showInfo slot SkyGui. Message: %1").arg(message));
}

void SkyGui::updateAffichage(QList<SkyGuiElement*> *elements)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("updateAffichage slot SkyGui -> not implemented"));
    emit startRepaintSky(elements);
}

void SkyGui::receiveStartAffichage()
{
    emit startAffichage();
}
