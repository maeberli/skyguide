#ifndef SKYDATABASE_H
#define SKYDATABASE_H

#include <QList>

#include <skycomponent.h>
#include <skyelement.h>
#include <skyrange.h>

class SkyDatabase : public SkyComponent
{
public:
    explicit SkyDatabase(QObject *parent = 0);

    QList<SkyElement*> getSkyElements(const SkyRange & range);

public slots:
    virtual void start();
    virtual void stop();
};

#endif // SKYDATABASE_H
