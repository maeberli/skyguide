#ifndef SKYPOSITION_H
#define SKYPOSITION_H

class SkyPosition
{
public:
    SkyPosition(double latitude, double longitude);
    double getLatitude() const
    {
        return p_latitude;
    }
    double getLongitude() const
    {
        return p_longitude;
    }
private:
    double p_latitude;
    double p_longitude;
};

#endif // SKYPOSITION_H
