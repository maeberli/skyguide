/**
  * Class declaration file of SkyConfiguration.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYCONFIGURATION_H
#define SKYCONFIGURATION_H

//include Qt-headers
#include <QObject>
#include <QSettings>

#define INIFILENAME "SkyGuide.ini"      //< defines the name of the configuration file.

/**
  * Class provides functionality to get config items stored in a config file.
  */
class SkyConfiguration : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor, set up object.
      *
      * This class will create a config-file in the application path.
      */
    explicit SkyConfiguration(QObject *parent = 0);

    /**
      * Returns a config item in the config file.
      *
      * if no value is specified in the config file,
      * this functions returns the default-value passed as argument
      * and stores the default value in the file..
      *
      * @param itemName     name of the item that should be read from the config file.
      * @param defValaue    default value that will be stored and returned if no item is found.
      * @return             the value if itemName exists, value passed as argument defValue if not.
      */
    QVariant getConfItem(QString itemName, QVariant defValue);

private:
    QSettings p_setObj;     //< objects for the access to the config file

};

#endif // SKYCONFIGURATION_H
