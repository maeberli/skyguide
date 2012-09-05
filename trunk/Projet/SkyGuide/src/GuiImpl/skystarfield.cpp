/**
  * Class implementation file of MainWindow.
  *
  * @author Matthieu Rossier
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QList>
#include <QMouseEvent>
#include <QFont>

#include "skystarfield.h"
#include "skyguielement.h"
#include "skycalculator.h"

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
    p_xP = 0.0;
    p_yP = 0.0;
    p_selection = 0;
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

    // pen.drawText(10, 10, "(" + QString::number(p_globalPos.x()) + ", " + QString::number(p_globalPos.y()) + ")");
    /******************************/

    pen.drawEllipse(30, 30, p_width * 2.0 - 60, p_height * 2.0 - 60);

    pen.translate(p_width, p_height);

    if (p_stars)
    {
        // Dessin du pointeur.
        pen.setPen(QPen(QBrush(Qt::red), 1));
        /***********************/
        // p_xP = -p_xP; /********** bricolage ***********/
        pen.drawLine(-p_xP - 20, p_yP, -p_xP + 20, p_yP);
        pen.drawLine(-p_xP, p_yP - 20, -p_xP, p_yP + 20);
        pen.drawRect(-p_xP - 8, p_yP - 8, 16, 16);
        /***********************/
        pen.setPen(Qt::SolidLine);

        pen.setPen(Qt::NoPen);
        pen.setBrush(QBrush(Qt::white));

        int count = p_stars->count();

        double magnitude = 0.0;

        for (int i = 0; i < count; ++i)
        {   
            magnitude = p_stars->at(i)->getMagnitude();

            /*
            if (!p_selections.empty())
            {
                int count = p_selections.count();
                for (int j = 0; j < count; ++j)
                    if (p_selections[j] == i)
                        pen.setBrush(QBrush(Qt::red));
            }
            */
            if (!p_selections.empty())
            {
                if (p_selections[p_selection] == i)
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

void SkyStarField::Inc(int index)
{
    p_selection = index;
    repaint();
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
    p_globalPos = mousePose;

    if (p_stars)
    {
        int count = p_stars->count();

        for (int i = 0; i < count; ++i)
        {
            if (abs(p_stars->at(i)->getPositionX() - mousePose.x()) < 7 &&
                abs(p_stars->at(i)->getPositionY() - mousePose.y()) < 7)
            {
                p_selections.append(i);
            }
        }

        // p_selection = p_selections[0];
        p_selection = 0;

        repaint();

        emit sendInfo(p_selections, p_stars);

        if (p_selections.isEmpty())
            emit sendClearText();
    }
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
            {
                resize(size() * p_factor);
                /***************/
                // p_xP *= p_factor;
                // p_yP *= p_factor;
                /***************/
            }
            p_width *= p_factor;
            p_height *= p_factor;
            p_cpt++;
            /***************/
            p_xP *= p_factor;
            p_yP *= p_factor;
            /***************/
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
            /***************/
            p_xP /= p_factor;
            p_yP /= p_factor;
            /***************/
            emit sendAdjust(false);
        }
    }
    if (p_stars)
    {
        int count = p_stars->count();
        for (int i = 0; i < count; ++i)
        {
            SkyCalculator::projectOnPlane(p_stars->at(i), &newX, &newY, p_width - 30);
            /*****/
            newY = -newY;
            /*****/
            p_stars->at(i)->setPositionX(newX);
            p_stars->at(i)->setPositionY(newY);
        }
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

void SkyStarField::setXP(double xp)
{
    p_xP = xp;
}

void SkyStarField::setYP(double yp)
{
    p_yP = yp;
}
