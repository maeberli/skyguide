#include "skyrange.h"

SkyRange::SkyRange(int azimut, int inclinasion)
{
    p_azimut = azimut;
    p_inclinasion = inclinasion;
}

int SkyRange::getAzimut()
{
    return p_azimut;
}

int SkyRange::getInclinasion()
{
    return p_inclinasion;
}
