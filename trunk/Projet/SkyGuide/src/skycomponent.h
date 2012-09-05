/**
  * Class declaration file of VectorOperations.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYCOMPONENT_H
#define SKYCOMPONENT_H

//include Qt-headers
#include <QObject>

//include SkyGuide specific headers
#include <skyloggertypes.h>
#include <skyconfiguration.h>

/**
  * Abstract SkyComponent defines a basic functionality/interface,
  * that every component (external device, database, ..) should respect.
  */
class SkyComponent : public QObject
{
    Q_OBJECT
public:
    /**
      * Consctructor, initalize an object
      *
      * @param config   constant pointer to a config object, which a component could use.
      * @param parent   parent object (Qt-specific)
      */
    SkyComponent(SkyConfiguration* const config, QObject* parent = 0);

signals:
    /**
      * Signal that a component can emit to log a message.
      *
      * @param type     Type of the message to log.
      * @param message  Text to log.
      */
    void logMessage(SKYLOGGER::SkyLoggerTypes type, const QString& message);

public slots:
    /**
      * Abstract public slot let the component begin its work.
      */
    virtual void start() = 0;
    /**
      * Abstract public slot let the component stop its work.
      */
    virtual void stop() = 0;

protected:
    SkyConfiguration* const p_config;   //< const reference to the configuration object.

};

#endif // SKYCOMPONENT_H
