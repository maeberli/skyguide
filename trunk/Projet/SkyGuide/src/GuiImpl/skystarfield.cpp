#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QList>
#include <QMouseEvent>
#include <QFont>

#include "skystarfield.h"
#include "skyguielement.h"
#include "skytransformation.h"

SkyStarField::SkyStarField(QWidget *parent) : QWidget(parent)
{
    p_width = 350.0;
    p_height = 350.0;
    p_cpt = 0;
    p_factor = 1.25;
    p_numDegree = 0;
    setMinimumSize(p_width * 2.0, p_height * 2.0);
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    p_stars = 0;
}

void SkyStarField::paintEvent(QPaintEvent *event)
{
    QPainter pen(this);
    pen.setFont(QFont("Arial Black", 10));
    /******************************/
    QRect align = rect(); // , circle = rect();
    align.setRect(10, 10, align.width() - 20, align.height() - 20);
    // circle.setRect(30, 30, circle.width() - 60, circle.height() - 60);
    // pen.drawRect(align);
    // pen.drawRect(circle);

    pen.drawText(align, Qt::AlignHCenter, QString("N"));
    pen.drawText(align, Qt::AlignHCenter | Qt::AlignBottom, QString("S"));
    pen.drawText(align, Qt::AlignVCenter | Qt::AlignLeft, QString("E"));
    pen.drawText(align, Qt::AlignVCenter | Qt::AlignRight, QString("W"));
    /******************************/

    pen.drawEllipse(30, 30, p_width * 2.0 - 60, p_height * 2.0 - 60);

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
                pen.drawEllipse(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 7, 7);
            else if (magnitude <= 2)
                pen.drawEllipse(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 6, 6);
            else if (magnitude <= 3)
                pen.drawRect(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 3, 3);
            else if (magnitude <= 4)
                pen.drawRect(p_stars->at(i)->getPositionX(), p_stars->at(i)->getPositionY(), 2, 2);

            pen.setBrush(QBrush(Qt::white));
        }
    }
}

void SkyStarField::mouseMoveEvent(QMouseEvent *event)
{
    int diffx = abs(event->pos().x() - prev.x());
    int diffy = abs(event->pos().y() - prev.y());
    if (event->pos().x() < prev.x() && diffx > 10)
    {
        emit ( sendMove(1) );
        prev = event->pos();
    }
    if (event->pos().x() > prev.x() && diffx > 10)
    {
        emit ( sendMove(2) );
        prev = event->pos();
    }
    if (event->pos().y() < prev.y() && diffy > 10)
    {
        emit ( sendMove(3) );
        prev = event->pos();
    }
    if (event->pos().y() > prev.y() && diffy > 10)
    {
        emit ( sendMove(4) );
        prev = event->pos();
    }
}

void SkyStarField::mousePressEvent(QMouseEvent *event)
{
    /**********************/
    setCursor(Qt::ClosedHandCursor);
    /**********************/
    p_selections.clear();
    QPointF mousePose = event->posF();
    mousePose.setX(mousePose.x() - p_width);
    mousePose.setY(mousePose.y() - p_height);

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

    if (p_selections.isEmpty())
        emit sendClearText();
}

void SkyStarField::mouseReleaseEvent(QMouseEvent *)
{
    setCursor(Qt::ArrowCursor);
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
            emit sendAdjust(true);
        }
    }
    else
    {
        if (!(p_cpt <= 0))
        {
            resize(size() / p_factor);
            p_width /= p_factor;
            p_height /= p_factor;
            p_cpt--;
            emit sendAdjust(false);
        }
    }
    int count = p_stars->count();
    for (int i = 0; i < count; ++i)
    {
        SkyTransformation::projection(p_stars->at(i), &newX, &newY, p_width - 30);
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
