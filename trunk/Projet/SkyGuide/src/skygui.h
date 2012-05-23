#ifndef SKYGUI_H
#define SKYGUI_H

#include <skycomponent.h>
#include <skyguielement.h>
#include "GuiImpl/mainwindow.h"

class SkyGui : public SkyComponent
{
    Q_OBJECT
public:
    SkyGui(SkyConfiguration* config, QObject *parent = 0);
    ~SkyGui();
    void showWindow();

signals:
    void startAffichage();
    void stopAffichage();

public slots:
    virtual void start();
    virtual void stop();

    void showWarning(const QString & message);
    void showError(const QString & message);
    void showInfo(const QString & message);
    void updateAffichage(const QList<SkyGuiElement*>& elements);
private:
    MainWindow *p_win;
};

#endif // SKYGUI_H
