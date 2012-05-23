#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    double _height;
    double _azimuth;
    double _angle;
    double _x;
    double _y;
public:
    static const double PI = 3.1415926;
    Position();
    void process(double rightAscension, double declinaison, double latitude, double longitude);
    void projection();
    void hour();
};

#endif // POSITION_H
