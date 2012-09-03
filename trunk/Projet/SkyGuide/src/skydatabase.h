/**
  * Class declaration file of CmdAccelerometer.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYDATABASE_H
#define SKYDATABASE_H

#include <QList>

#include <skycomponent.h>
#include <skyelement.h>

class SkyDatabase : public SkyComponent
{
    Q_OBJECT
public:
    explicit SkyDatabase(SkyConfiguration* config, QObject *parent = 0);

    QList<SkyElement*>* getSkyElements();

public slots:
    void start() { }
    void stop() { }
};

#endif // SKYDATABASE_H
