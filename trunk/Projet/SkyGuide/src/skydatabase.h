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
    virtual void start() { }
    virtual void stop() { }
};

#endif // SKYDATABASE_H
