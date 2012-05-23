#include "Place.h"

Place::Place(double latitude, double longitude)
{
    _latitude = latitude / 180 * 3.14;
    _longitude = longitude / 180 * 3.14;
}
