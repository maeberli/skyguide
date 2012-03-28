#ifndef SKYCALCULATOR_H
#define SKYCALCULATOR_H

#include <skycomponent.h>
#include <skyrange.h>
#include <skyelement.h>
#include <skyguielement.h>

class SkyCalculator : public SkyComponent
{
    Q_OBJECT
public:
    SkyCalculator(SkyConfiguration* config, QObject *parent = 0);

    SkyRange getSkyRange(int positionData, int direction, int slope, int inclLefRight);
    QList<SkyGuiElement*>* convert2GuiElements(const QList<SkyElement*> & elements);
signals:

public slots:
    virtual void start();
    virtual void stop();

};

#endif // SKYCALCULATOR_H
