#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QList>
#include <QMouseEvent>
#include <QAbstractScrollArea>

#include "skystarfield.h"
#include "skyguielement.h"
#include "skytransformation.h"

SkyStarField::SkyStarField(QWidget *parent) : QWidget(parent)
{
    p_width = 500;
    p_height = 500;
    p_cpt = 0;
    p_factor = 1.25;
    p_numDegree = 0;
    setMinimumSize(p_width * 2, p_height * 2);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    setMouseTracking(true);
    p_stars = 0;
}

void SkyStarField::paintEvent(QPaintEvent *event)
{
    QPainter pen(this);

    pen.drawEllipse(0, 0, p_width * 2, p_height * 2);

    pen.translate(p_width, p_height);

    pen.setBrush(QBrush(Qt::white));

    pen.setPen(Qt::NoPen);

    if (p_stars)
    {
        int count = p_stars->count();

        double magnitude = 0.0;

        for (int i = 0; i < count; ++i)
        {   
            magnitude = p_stars->at(i)->getMagnitude();

            if (!p_selections.empty())
            {
                int count = p_selections.count();
                for (int j = 0; j < count; ++j)
                    if (p_selections[j] == i)
                        pen.setBrush(QBrush(Qt::red));
            }

            if (magnitude >= 0.0 && magnitude <= 1)
                pen.drawEllipse(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 8, 8);
            else if (magnitude <= 2)
                pen.drawEllipse(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 6, 6);
            else if (magnitude <= 3)
                pen.drawEllipse(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 4, 4);
            else if (magnitude <= 6)
                pen.drawEllipse(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 2, 2);

            pen.setBrush(QBrush(Qt::white));
        }
    }
}

void SkyStarField::mouseMoveEvent(QMouseEvent *event)
{
    // qDebug() << event->pos();
}

void SkyStarField::mousePressEvent(QMouseEvent *event)
{
    p_selections.clear();
    QPointF mousePose = event->posF();
    mousePose.setX(mousePose.x() - p_width);
    mousePose.setY(mousePose.y() - p_height);
    // mousePose.setY(-mousePose.y());
    qDebug() << mousePose;

    int count = p_stars->count();

    for (int i = 0; i < count; ++i)
    {
        if (abs(p_stars->at(i)->getPositionX() - mousePose.x()) < 7 &&
            abs(p_stars->at(i)->getPositionY() - mousePose.y()) < 7)
        {
            p_selections.append(i);
        }
    }

    repaint();

    emit sendInfo(p_selections, p_stars);
}

void SkyStarField::wheelEvent(QWheelEvent *event)
{
    p_numDegree = event->delta() / 8;
    double newX = 0.0, newY = 0.0;
    if (p_numDegree > 0)
    {
        if (!(p_cpt > 10))
        {
            if (!(p_cpt < 0))
                resize(size() * p_factor);
            p_width *= p_factor;
            p_height *= p_factor;
            p_cpt++;
        }
    }
    else
    {
        if (!(p_cpt < -5))
        {
            resize(size() / p_factor);
            p_width /= p_factor;
            p_height /= p_factor;
            p_cpt--;
        }
    }
    int count = p_stars->count();
    for (int i = 0; i < count; ++i)
    {
        SkyTransformation::projection(p_stars->at(i), &newX, &newY, p_width);
        p_stars->at(i)->setPositionX(newX);
        p_stars->at(i)->setPositionY(newY);
    }
    repaint();
}

void SkyStarField::clearSelection()
{
    p_selections.clear();
    repaint();
}

void SkyStarField::setStars(QList<SkyGuiElement *> *stars)
{
    p_stars = stars;
}
