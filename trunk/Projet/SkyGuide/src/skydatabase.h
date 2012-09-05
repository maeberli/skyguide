/**
  * Class declaration file of SkyDatabase.
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

/**
  * Class who represent the control and access database.
  */
class SkyDatabase : public SkyComponent
{
    Q_OBJECT
public:
    /**
      * Constructor, creates and initialize the object.
      *
      * @param config     Represent the file configuration.
      * @param parent     Represent object who inialize it.
      */
    explicit SkyDatabase(SkyConfiguration* config, QObject *parent = 0);

    /**
      * Load to memory contains of file database (SkyGuide.db).
      */
    QList<SkyElement*>* getSkyElements();

public slots:
    /**
      * Slot who start communication with database.
      */
    void start() { }

    /**
      * Slot who stop communication with databas.
      */
    void stop() { }
};

#endif // SKYDATABASE_H
