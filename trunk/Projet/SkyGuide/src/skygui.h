/**
  * Class declaration file of SkyGui.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYGUI_H
#define SKYGUI_H

//include Qt-headers
#include <QList>

//include SkyGuide specific headers
#include <skycomponent.h>
#include <skyguielement.h>
#include "GuiImpl/mainwindow.h"
#include "GuiImpl/skystarfield.h"
#include "skyguielement.h"

/**
  * Implementatino of the GUI component of the SkyGuide.
  */
class SkyGui : public SkyComponent
{
    Q_OBJECT
public:
    /**
      * Consctructor, initalize an object
      *
      * @param config   constant pointer to a config object, which the GUI could use.
      * @param parent   parent object (Qt-specific)
      */
    SkyGui(SkyConfiguration* config, QObject *parent = 0);

    /**
      * Destructor, cleanup.
      */
    ~SkyGui();

     /**
       * Shows the GUI-Window.
       */
    void showWindow();

signals:
    /**
      * Signales that the start button is pressed on the GUI.
      */
    void startAffichage();

    /**
      * Signales that the stop button is pressed on the GUI.
      */
    void stopAffichage();

    /**
      * signales that the gui with the element shoud be repainted.
      *
      * @param stars    list to the elements to show.
      * @param xP       x component of the pointer position.
      * @param yP       y component of the pointer position.
      */
    void startRepaintSky(QList<SkyGuiElement *> *stars, double xP, double yP);

public slots:
    /**
      * No functionality implemented. Not used for core component.
      */
    void start() { }

    /**
      * No functionality implemented. Not used for core component.
      */
    void stop() { }

    /**
      * shows the passed message as warning in the log section on the GUI.
      *
      * @param message  Message-text to show.
      */
    void showWarning(const QString & message);

    /**
      * shows the passed message as error in the log section on the GUI.
      *
      * @param message  Message-text to show.
      */
    void showError(const QString & message);

    /**
      * shows the passed message as info in the log section on the GUI.
      *
      * @param message  Message-text to show.
      */
    void showInfo(const QString & message);

    /**
      * Repaints the Sky on the gui with the passed stars and sets the pointer to xP and yP.
      *
      * @param stars    list to the elements to show.
      * @param xP       x component of the pointer position.
      * @param yP       y component of the pointer position.
      */
    void updateAffichage(QList<SkyGuiElement *> *elements, double xP, double yP);

private slots:
    /**
      * If called this slots emit the startAffichage signal.
      */
    void receiveStartAffichage();
    /**
      * If called this slots emit the stopAffichage signal.
      */
    void receiveStopAffichage();

private:
    MainWindow *p_win;
};

#endif // SKYGUI_H
