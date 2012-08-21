#ifndef SKYSTARFIELD_H
#define SKYSTARFIELD_H

#include <QObject>
#include <QWidget>
#include <QList>
#include "skyguielement.h"

class SkyStarField : public QWidget
{
    Q_OBJECT

public:

    SkyStarField(QWidget *parent = 0);

    void setStars(QList<SkyGuiElement *> *stars);

public slots:
    void clearSelection();


signals:

    void sendInfo(QList<int> selections, QList<SkyGuiElement *> *stars);

protected:

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

private:

    QList<SkyGuiElement *> *p_stars;

    QList<int> p_selections;

    int p_width;

    int p_height;

    int p_cpt;

    double p_factor;

    int p_numDegree;
};

#endif // SKYSTARFIELD_H
