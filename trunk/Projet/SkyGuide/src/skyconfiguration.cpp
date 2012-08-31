/**
  * Class implementation file of SkyConfiguration.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "skyconfiguration.h"

#include <QtCore/QCoreApplication>

SkyConfiguration::SkyConfiguration(QObject *parent) :
    QObject(parent),
    p_setObj(QCoreApplication::applicationDirPath()+"/"+INIFILENAME, QSettings::IniFormat)
{
}

QVariant SkyConfiguration::getConfItem(QString itemName, QVariant defValue)
{
    QVariant retItem = defValue;

    if(p_setObj.contains(itemName))
        retItem = p_setObj.value(itemName, defValue);
    else
        p_setObj.setValue(itemName, defValue);

    return retItem;
}
