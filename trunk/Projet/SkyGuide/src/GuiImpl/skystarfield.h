/**
  * Class declaration file of SkyStarField.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYSTARFIELD_H
#define SKYSTARFIELD_H

//include Qt-headers
#include <QObject>
#include <QWidget>
#include <QList>
#include <QScrollBar>

//include SkyGuide specific headers
#include "skyguielement.h"

/**
  * Class who represent the view of sky of our application.
  *
  * This class describle widget sky.
  */
class SkyStarField : public QWidget
{
    Q_OBJECT

public:

    /**
      * Constructor, creates and initialize the object.
      *
      * @param parent     Represent widget parent.
      */
    SkyStarField(QWidget *parent = 0);

    /**
      * Apply list of stars.
      *
      * @param stars   Represent the stars to display.
      */
    void setStars(QList<SkyGuiElement *> *stars);

    /**
      * Apply the coordinate x of pointer for display to sky.
      *
      * @param xp   Coordinate x of pointer.
      */
    void setXP(double xp);

    /**
      * Apply the coordinate y of pointer for display to sky.
      *
      * @param yp   Coordinate y of pointer.
      */
    void setYP(double yp);

public slots:
    /**
      * Slot who clear selection stars.
      */
    void clearSelection();

    /**
      * Slot who increment index selection star.
      *
      * @param index   Represent the index of selection star.
      */
    void Inc(int index);


signals:

    /**
      * Signal who send stars selection to GUI (MainWindow).
      *
      * @param selections   Represent selections stars.
      * @param stars        Represen all stars.
      */
    void sendInfo(QList<int> selections, QList<SkyGuiElement *> *stars);

    /**
      * Signal who send the information to adjust the horizontal/vertical scrollbar.
      *
      * @param in   Zoom '+' (true) or '-' (false).
      */
    void sendAdjust(bool in);

    /**
      * Signal who send the information to deplace wiget with mouse.
      *
      * @param direction   Represent the direction (right (1), left (2), up (3), down (4)).
      */
    void sendMove(int direction);

    /**
      * Signal who send the information to clear text (Label and TextEdit).
      */
    void sendClearText();

protected:

    /**
      * Event who repaint the widget (SkyStarField), with an object "QPainter".
      *
      * @param event   Information of event.
      */
    void paintEvent(QPaintEvent *event);

    /**
      * Event who active when mouse deplace in widget.
      *
      * @param event   Information of event.
      */
    void mouseMoveEvent(QMouseEvent *event);

    /**
      * Event who active when mouse was pressed in widget.
      *
      * @param event   Information of event.
      */
    void mousePressEvent(QMouseEvent *event);

    /**
      * Event who active when mouse was released in widget.
      *
      * @param event   Information of event.
      */
    void mouseReleaseEvent(QMouseEvent *);

    /**
      * Event who active when wheel mouse is actvated.
      *
      *@param event   Information of event.
      */
    void wheelEvent(QWheelEvent *event);

private:

    QList<SkyGuiElement *> *p_stars;      //< Represent all of stars.
    double p_xP;                          //< Coordinate x of pointer.
    double p_yP;                          //< Coordinate y of pointer.
    QPointF p_globalPos;                  //< Coordinate (x et y) of mouse.
    QList<int> p_selections;              //< List of selections stars.
    double p_width;                       //< Width of widget sky.
    double p_height;                      //< Height of widget sky.
    int p_cpt;                            //< Compter.
    double p_factor;                      //< Factor zoom.
    int p_numDegree;                      //< Degree of zoom (wheel).
    QPoint prev;                          //< Coordinate (x et y) of previous mouse.
    int p_selection;                      //< Index of selection star.
};

#endif // SKYSTARFIELD_H
