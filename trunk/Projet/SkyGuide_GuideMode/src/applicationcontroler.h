#ifndef APPLICATIONCONTROLER_H
#define APPLICATIONCONTROLER_H

#include <QObject>

#include "guidemodehandler.h"

class ApplicationControler : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationControler(
            double azimuth,
            double altitude,
            bool verboseOutput,
            QObject *parent = 0);
    
signals:
    void finished();
    
public slots:
    void start();

private slots:
    void finish();

private:
    const double m_azimuth;
    const double m_altitude;
    const bool m_VERBOSEOUTPUT;
    GuideModeHandler* m_handler;



};

#endif // APPLICATIONCONTROLER_H
