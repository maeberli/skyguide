#include "skyposition.h"

SkyPosition::SkyPosition(double latitude, double longitude)
{
    double PI = 3.14159265;
    p_latitude = latitude * PI / 180;
    p_longitude = longitude * PI / 180;
}
