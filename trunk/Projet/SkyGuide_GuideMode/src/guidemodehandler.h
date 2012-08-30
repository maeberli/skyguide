#ifndef GUIDEMODEHANDLER_H
#define GUIDEMODEHANDLER_H

#include <QObject>
#include <QTimer>
#include "ExternalDeviceImpl/starpointercommunication.h"
#include "CalculatorImpl/vectoroperations.h"


using namespace ExternalDeviceImpl;
using namespace CalculatorImpl;

class GuideModeHandler : public QObject
{
    Q_OBJECT
    enum Direction{
        Top         = 0,
        TopLeft     = 1,
        Left        = 2,
        BottomLeft  = 3,
        Bottom      = 4,
        BottomRight = 5,
        Right       = 6,
        TopRight    = 7,
        Undef       = 8
    };

public:
    GuideModeHandler(
            double _refAzimuth,
            double _refAltitude,
            bool verboseOutput = false,
            QObject *parent = 0);
    ~GuideModeHandler();

    QString DirectionToString(Direction dir)
    {
        switch(dir)
        {
        case Top:
            return "Top";
            break;
        case TopLeft:
            return "TopLeft";
            break;
        case Left:
            return "Left";
            break;
        case BottomLeft:
            return "BottomLeft";
            break;
        case Bottom:
            return "Bottom";
            break;
        case BottomRight:
            return "BottomRight";
            break;
        case Right:
            return "Right";
            break;
        case TopRight:
            return "TopRight";
            break;
        case Undef:
            return "Undef";
            break;
        default:
            return "UNKNOW DIRECTION";
        }
    }

private slots:
    void logError(QString msg);
    void logInfo(QString msg);
    void logVerbose(QString msg);
    void handleReceivedAccelormeterData(int compX,int compY,int compZ);
    void handleReceivedGPSData(double longitude, double latitude);
    void handleReceivedMagnetometerData(int compX,int compY,int compZ);

    void sendNewDirection();

private:
    QTimer* m_calcTicker;
    StarPointerCommunication* m_com;
    double m_refAzimuth;
    double m_refAltitude;
    const double m_VERBOSEOUTPUT;

    int m_actAccCompX;
    int m_actAccCompY;
    int m_actAccCompZ;
    int m_actMagCompX;
    int m_actMagCompY;
    int m_actMagCompZ;
    double m_actLongitude;
    double m_actLatitude;

    Direction direction;


};

#endif // GUIDEMODEHANDLER_H
