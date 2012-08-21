#ifndef SKYTRANSFORMATION_H
#define SKYTRANSFORMATION_H

#include <QDate>
#include <QTime>

#include "skyposition.h"
#include "skyelement.h"
#include "skyguielement.h"

class SkyTransformation
{
public:
    static double getAngle();
    static void transformation(SkyElement *star, SkyPosition *where, double angle);
    static void projection(SkyElement *star, double *x, double *y, int factor);
};

#endif // SKYTRANSFORMATION_H
