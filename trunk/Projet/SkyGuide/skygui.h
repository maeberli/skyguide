#ifndef SKYGUI_H
#define SKYGUI_H

#include <skycomponent.h>
#include <skyguielement.h>

class SkyGui : public SkyComponent
{
    Q_OBJECT
public:
    SkyGui(QObject *parent = 0);
    ~SkyGui();

signals:
    void startAffichage();
    void stopAffichage();

public slots:
    virtual void start();
    virtual void stop();

    void showWarning(const QString & message);
    void showError(const QString & message);
    void showInfo(const QString & message);
    void updateAffichage(QList<SkyGuiElement*> elements);
};

#endif // SKYGUI_H
