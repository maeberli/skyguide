#include <cmath>

#include "Star.h"

Star::Star() : _rightAscension(0.0), _declinaison(0), _magnitude(0) {}

Star::Star(double rightAscension, double declinaison, double magnitude) : _magnitude(magnitude)
{
    _rightAscension =  rightAscension / 180 * 3.14;
    _declinaison = declinaison / 180 * 3.14;
}
