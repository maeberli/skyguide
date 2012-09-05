/**
  * Class declaration file of MainWindow.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QList>
#include <QLabel>

#include "GuiImpl/skystarfield.h"
#include "skyguielement.h"

/**
  * Class who represent the view of our application.
  *
  * This class contains all widgets.
  */
class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    /**
      * Constructor, creates and initialize the object.
      *
      * @param parent     Represent widget parent.
      */
    MainWindow(QWidget *parent = 0);

    /**
      * Destructor, does the cleanup.
      */
    ~MainWindow();

    /**
      * Display message log in log box.
      *
      * @param message   Represent the message of the log.
      */
    void appendLogMessage(QString message);

public slots:
    /**
      * Slot who repaint the widget sky.
      *
      * @param stars   The stars of the sky.
      * @param xP      Position x of the pointer.
      * @param yP      Position y of the pointer.
      */
    void repaintSky(QList<SkyGuiElement *> *stars, double xP, double yP);

    /**
      * Slot who selection the stars.
      *
      * @param selections   Index of the stars in twice parameters.
      * @param stars        The stars of the sky.
      */
    void updateInfo(QList<int> selections, QList<SkyGuiElement *> *stars);

    /**
      * Slot who clear text of log box.
      */
    void clearText();

    /**
      * Slot who adjust the horizontal and vertical scrollbar.
      *
      * @param in   Apply a zoom + or -.
      */
    void adjustScrollBar(bool in);

    /**
      * Slot who deplace the widget sky with the mouse.
      *
      * @param direction   Parameter direction: right, left, up, down.
      */
    void drag(int direction);

    /**
      * Slot who start display widget sky.
      */
    void startStop();

    /**
      * Slot who change star selection.
      */
    void next();

    void previous();

signals:
    /**
      * Signal who reset stars selection.
      */
    void resetSelection();

    /**
      * Signal who start/stop display of sky.
      */
    void sendStartAffichage();
    void sendStopAffichage();

    /**
      * Signal who send next selection star.
      *
      * @param index   Represent index of stars selection.
      */
    void sendInc(int index);
    
private:
    QHBoxLayout *p_mainLayout;        //< Main layout.
    SkyStarField *p_sky;              //< Wiget who represent the sky.
    QVBoxLayout *p_rightLayout;       //< Right layout.
    QPushButton *p_mainButton;        //< Main button (start/stop).
    QGroupBox *p_logBox;              //< Area log box.
    QGroupBox *p_starBox;             //< Area star box.
    QVBoxLayout *p_logLayout;         //< Log layout.
    QTextEdit *p_log;                 //< Log text edit.
    QPushButton *p_logClear;          //< Log clear button.
    QScrollArea *p_zoom;              //< Zoom area.
    /*********************************/
    QGridLayout *p_grid;              //< Grid for the informations stars.
    QLabel *p_iDeclinaison;           //< Label text declinaison.
    QLabel *p_tDeclinaison;           //< Label text declinaison.
    QLabel *p_iRightAscension;        //< Label text right ascension.
    QLabel *p_tRightAscension;        //< Label text right ascension.
    QLabel *p_iAzimuth;               //< Label text azimuth.
    QLabel *p_tAzimth;                //< Label text azimuth.
    QLabel *p_iHeight;                //< Label text height.
    QLabel *p_tHeight;                //< Label text height.
    QLabel *p_iGreekLetter;           //< Label text greek letter.
    QLabel *p_tGreekLetter;           //< Label text greek letter.
    QLabel *p_iConstellation;         //< Label text constellation.
    QLabel *p_tConstellation;         //< Label text constellation.
    QLabel *p_iMagnitude;             //< Label text magnitude.
    QLabel *p_tMagnitude;             //< Label text magnitude.
    QPushButton *p_next;              //< Next star selection button.
    QPushButton *p_previous;          //< Previous star selection button.
    /*********************************/
    int p_index;                      //< Index selection star.
    QList<int> p_selections;          //< List selection stars.
    QList<SkyGuiElement *> *p_stars;  //< All of list stars.
};

#endif // MAINWINDOW_H
