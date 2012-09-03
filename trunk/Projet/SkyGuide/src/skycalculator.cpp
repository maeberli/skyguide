#include "skycalculator.h"

#include <QDate>
#include <QTime>

SkyCalculator::SkyCalculator(SkyConfiguration* config, QObject* parent) :
    SkyComponent(config, parent)
{
}

double SkyCalculator::getAngleHour()
{
    const double DPI = M_PI * 2;
    int jj = QDate::currentDate().toJulianDay();
    double century = (jj - 2451545.0) / 36525.0;
    double secondes = 24110.54841 + (8640184.812866 * century) + (0.093104 * (century * century)) - (0.0000062 * (century * century * century));
    double h = secondes / 3600.0;
    double H = ((h / 24.0) - int(h / 24.0)) * 24.0;
    double angleH = (DPI * H) / 23.93;
    int hour = QTime::currentTime().hour();
    int minute = QTime::currentTime().minute();
    double angleT = (hour - 12.0 + minute / 60.0 - 1.0) * DPI / 23.93;
    return angleH + angleT;
}

void SkyCalculator::toHorizontalCoord(SkyElement* star, double angle, double latitude, double longitude)
{
    double rightAscension = star->getRightAscension();
    double declinaison = star->getDeclination();
    double hourAngle = angle - rightAscension + longitude;

    double altitudeSin = sin(declinaison) * sin(latitude) - cos(declinaison) * cos(latitude) * cos(hourAngle);
    double altitude = asin(altitudeSin);
    star->setAltitude(altitude);

    double azimuthCos = (sin(declinaison) - sin(latitude) * sin(altitude)) / (cos(latitude) * cos(altitude));
    double azimuthSin = (cos(declinaison) * sin(hourAngle)) / cos(altitude);

    if (azimuthSin > 0.0)
        star->setAzimuth(fabs(acos(azimuthCos)));
    else
        star->setAzimuth(-fabs(acos(azimuthCos)));
}

void SkyCalculator::projectOnPlane(SkyElement* star, double* x, double* y, int factor)
{
    double azimuth = star->getAzimuth();
    double altitude = star->getAltitude();
    const double PIDIV2 = -2.0 / M_PI;
    double dist = -factor * (PIDIV2 * altitude + 1.0);
    *x = dist * cos(azimuth-M_PI/2);
    *y = dist * sin(azimuth-M_PI/2);
}

void SkyCalculator::projectOnPlane(double azimuth, double height, double* x, double* y, int factor)
{
    const double PIDIV2 = -2.0 / M_PI;
    double dist = -factor * (PIDIV2 * height + 1.0);
    *x = dist * cos(azimuth-M_PI/2);
    *y = dist * sin(azimuth-M_PI/2);
}

QList<SkyGuiElement*>* SkyCalculator::convert2GuiElements(const QList<SkyElement*> &elements)
{
    QList<SkyGuiElement*>* guiElements =  new QList<SkyGuiElement*>();

    foreach(SkyElement* element, elements)
    {
        guiElements->append(new SkyGuiElement(*element,0,0));
    }

    return guiElements;
}

