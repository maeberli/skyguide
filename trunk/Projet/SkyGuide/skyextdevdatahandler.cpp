#include "skyextdevdatahandler.h"

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
    //TODO: Implementation

    //if local data changed emit new signal newExtDataAvailable(...)
    //  set last members variables
//        p_lSlope = p_slope;
//        p_lInclLefRight = p_inclLefRight;
//        p_lDirection = p_direction;
//        p_lPositionData = p_positionData;


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
