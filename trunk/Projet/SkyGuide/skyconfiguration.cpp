#include "skyconfiguration.h"

SkyConfiguration::SkyConfiguration(QObject *parent) :
    QObject(parent),
    p_setObj(INIFILENAME, QSettings::IniFormat)
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
