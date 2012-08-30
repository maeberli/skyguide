#include "applicationcontroler.h"

#include <QTimer>

ApplicationControler::ApplicationControler(
        double azimuth,
        double altitude,
        bool verboseOutput,
        QObject *parent) :
    QObject(parent),
    m_azimuth(azimuth),
    m_altitude(altitude),
    m_VERBOSEOUTPUT(verboseOutput)
{
}

#include <QThread>
void ApplicationControler::start()
{
    m_handler = new GuideModeHandler(m_azimuth, m_altitude, m_VERBOSEOUTPUT);

    QTimer::singleShot(180*1000, this, SLOT(finish()));
}

void ApplicationControler::finish()
{
    delete m_handler;
    emit finished();
}
