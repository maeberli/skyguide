#ifndef SKYCONFIGURATION_H
#define SKYCONFIGURATION_H

#include <QObject>
#include <QSettings>

#define INIFILENAME "SkyGuide.ini"

class SkyConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit SkyConfiguration(QObject *parent = 0);

    QVariant getConfItem(QString itemName, QVariant defValue);

private:
    QSettings p_setObj;

};

#endif // SKYCONFIGURATION_H
