/**
  * Class declaration file of CmdAccelerometer.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef SKYSTARFIELD_H
#define SKYSTARFIELD_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QScrollBar>
#include "skyguielement.h"

class SkyStarField : public QWidget
{
    Q_OBJECT

public:

    SkyStarField(QWidget *parent = 0);

    void setStars(QList<SkyGuiElement *> *stars);
    void setXP(double xp);
    void setYP(double yp);

public slots:
    void clearSelection();
    void Inc(int index);


signals:

    void sendInfo(QList<int> selections, QList<SkyGuiElement *> *stars);
    void sendAdjust(bool in);
    void sendMove(int direction);
    void sendClearText();

protected:

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *event);

private:

    QList<SkyGuiElement *> *p_stars;

    double p_xP;

    double p_yP;

    QPointF p_globalPos;

    QList<int> p_selections;

    double p_width;

    double p_height;

    int p_cpt;

    double p_factor;

    int p_numDegree;

    QPoint prev;

    int p_selection;
};

#endif // SKYSTARFIELD_H
