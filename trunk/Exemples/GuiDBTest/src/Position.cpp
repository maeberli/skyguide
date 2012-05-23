#include <QDate>
#include <QDebug>
#include <cmath>

#include "Position.h"

Position::Position() : _height(0.0), _azimuth(0.0), _angle(0.0), _x(0.0), _y(0.0) { }

void Position::process(double rightAscension, double declinaison, double latitude, double longitude)
{
    double H = _angle - rightAscension + longitude;
    double heightSin = sin(declinaison) * sin(latitude) - cos(declinaison) * cos(latitude) * cos(H);
    _height = asin(heightSin);

    double azimuthCos = (sin(declinaison) - sin(latitude) * sin(_height)) / (cos(latitude) * cos(_height));
    double azimuthSin = (cos(declinaison) * sin(H)) / cos(_height);

    if (azimuthSin > 0.0)
        _azimuth = acos(azimuthCos);
    else
        _azimuth = -acos(azimuthCos);
}

void Position::projection()
{
    if (_height > 0.0)
    {
        double dist = -300 * ((-2.0 / PI) * _height + 1.0);
        _x = dist * cos(_azimuth);
        _y = dist * sin(_azimuth);
        // qDebug() << "x: " << _x;
        // qDebug() << "y: " << _y;
    }
}

void Position::hour()
{
    int JJ = QDate::currentDate().toJulianDay();
    double T = (JJ - 2451545.0) / 36525.0;
    // qDebug() << "T: " << T;
    double H1 = 24110.54841 + (8640184.812866 * T) + (0.093104 * (T*T)) - (0.0000062 * ( T*T*T));
    // qDebug() << "H1: " << H1;
    double HSH = H1 / 3600.0;
    double HS = ((HSH / 24.0) - int(HSH / 24.0)) * 24.0;
    // qDebug() << "HS: " << HS;
    double angleH = (2.0 * PI * HS) / 23.93;
    // qDebug() << "angleH: " << angleH;
    int heur = QTime::currentTime().hour();
    int minute = QTime::currentTime().minute();
    double angleT = (heur - 12.0 + minute / 60.0 - 1.0) * (2.0 * PI) / 23.93;
    // qDebug() << "angleT: " << angleT;
    _angle = angleH + angleT;
    // qDebug() << "angle: " << _angle;
}
