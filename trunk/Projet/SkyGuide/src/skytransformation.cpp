#include <QDate>
#include <QTime>
#include <cmath>

#include "skytransformation.h"
#include "skyposition.h"
#include "skyelement.h"

double SkyTransformation::getAngle()
{
    double PI = 3.14159265;
    double DPI = 6.28318530;
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

void SkyTransformation::transformation(SkyElement *star, SkyPosition *where, double angle)
{
    double rightAscension = star->getRightAscension();
    double declinaison = star->getDeclinasion();
    double latitude = where->getLatitude();
    double longitude = where->getLongitude();
    double hourAngle = angle - rightAscension + longitude;

    double altitudeSin = sin(declinaison) * sin(latitude) - cos(declinaison) * cos(latitude) * cos(hourAngle);
    double altitude = asin(altitudeSin);
    star->setAltitude(altitudeSin);

    double azimuthCos = (sin(declinaison) - sin(latitude) * sin(altitude)) / (cos(latitude) * cos(altitude));
    double azimuthSin = (cos(declinaison) * sin(hourAngle)) / cos(altitude);

    if (azimuthSin > 0.0)
        star->setAzimuth(acos(azimuthCos));
    else
        star->setAzimuth(-acos(azimuthCos));
}

void SkyTransformation::projection(SkyElement *star, double *x, double *y, int factor)
{
    double azimuth = star->getAzimuth();
    double altitude = star->getAltitude();
    double PIDIV2 = -2.0 / 3.14159265;
    double dist = -factor * (PIDIV2 * altitude + 1.0);
    *x = dist * cos(azimuth);
    *y = dist * sin(azimuth);
}
