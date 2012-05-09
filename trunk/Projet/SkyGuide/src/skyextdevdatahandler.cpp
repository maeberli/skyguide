#include "skyextdevdatahandler.h"

#include <cmath>

//Intervall for checking updates in miliseconds
#define CHECKFORUPDATESINTERVAL 3000

//Minimum difference between old and new data
#define MINDIFFSLOPE 1.0
#define MINDIFFPOSITIONDATA 0.1
#define MINDIFFDIRECTION 0.1
#define MINDIFFINCLLEFTRIGHT 0.1

SkyExtDevDataHandler::SkyExtDevDataHandler(QObject *parent) :
    QObject(parent),
    p_slope(0),
    p_inclLefRight(0),
    p_direction(0),
    p_positionData(0),
    p_lSlope(0),
    p_lInclLefRight(0),
    p_lDirection(0),
    p_lPositionData(0)
{
  p_timer = new QTimer(this);
  connect(p_timer, SIGNAL(timeout()),
          this, SLOT(timerTimeout()));
  p_timer->start(CHECKFORUPDATESINTERVAL);
}

SkyExtDevDataHandler::~SkyExtDevDataHandler()
{
  delete p_timer;
}

void SkyExtDevDataHandler::timerTimeout()
{
    int diffSlope = std::abs(p_lSlope-p_slope);
    int diffInclLeftRight = std::abs(p_lInclLefRight-p_inclLefRight);
    int diffDirection = std::abs(p_lDirection-p_direction);
    int diffPositionData = std::abs(p_lPositionData-p_positionData);

    if(     diffSlope>MINDIFFSLOPE
            || diffInclLeftRight>MINDIFFINCLLEFTRIGHT
            || diffDirection>MINDIFFDIRECTION
            || diffPositionData>MINDIFFPOSITIONDATA)
    {
        p_lSlope = p_slope;
        p_lInclLefRight = p_inclLefRight;
        p_lDirection = p_direction;
        p_lPositionData = p_positionData;
        emit newExtDataAvailable(p_lSlope, p_lInclLefRight, p_lDirection, p_lPositionData);
    }
}

void SkyExtDevDataHandler::setPositionData(int positionData)
{
    p_positionData = positionData;
}

void SkyExtDevDataHandler::setDirectionData(int direction)
{
    p_direction = direction;
}

void SkyExtDevDataHandler::setOrientationData(int slope, int inclLeftRight)
{
    p_slope = slope;
    p_inclLefRight = inclLeftRight;
}
