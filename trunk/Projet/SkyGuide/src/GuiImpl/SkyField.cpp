#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMessageBox>

// #include "SkyField.h"
// #include "BrighStars.h"
// #include "Star.h"
// #include "Place.h"
// #include "Position.h"

/*#define P1X 110
#define P1Y 78
#define P2X 45
#define P2Y 100
#define P3X 78
#define P3Y 200*/

/*SkyField::SkyField(QWidget *parent) : QWidget(parent)
{
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
    starsProj = NULL;
}

void SkyField::drawSky(Star* starsSky, Place* where)
{   
    starsProj = new Position[1628];
    for (int i = 0; i < 1628; ++i)
    {
        starsProj[i].hour();
        starsProj[i].process(starsSky[i].getRightAscension(), starsSky[i].getDeclinaison(), where->_latitude, where->_longitude);
        starsProj[i].projection();
    }
    update();
}

void SkyField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.translate(400, 400);

    int counter = 0;
    int max_x = -10000, min_x = 10000, max_y = -10000, min_y = 10000;

    if (starsProj != NULL)
    {
        for (int i = 0; i < 1628; ++i)
        {
            if (starsProj[i]._x != 0.0 && starsProj[i]._y != 0.0)
            {
                painter.drawLine(starsProj[i]._x, starsProj[i]._y - 3, starsProj[i]._x, starsProj[i]._y + 3);
                painter.drawLine(starsProj[i]._x - 3, starsProj[i]._y, starsProj[i]._x + 3, starsProj[i]._y);
                painter.drawPoint(starsProj[i]._x, starsProj[i]._y);
                ++counter;
                if (starsProj[i]._x > max_x) max_x = starsProj[i]._x;
                if (starsProj[i]._x < min_x) min_x = starsProj[i]._x;
                if (starsProj[i]._y > max_y) max_y = starsProj[i]._y;
                if (starsProj[i]._y < min_y) min_y = starsProj[i]._y;
            }
        }
        painter.drawEllipse(-300, -300, (max_x - min_x) + 10, (max_y - min_y) + 10);
    }
}

SkyField::~SkyField()
{
    delete[] starsProj;
}*/
