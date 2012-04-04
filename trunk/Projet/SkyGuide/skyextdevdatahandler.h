#ifndef SKYEXTDEVDATAHANDLER_H
#define SKYEXTDEVDATAHANDLER_H

#include <QObject>
#include <QTimer>
#include <QList>

//Intervall for checking updates in miliseconds
#define CHECKFORUPDATESINTERVAL 3000

class SkyExtDevDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit SkyExtDevDataHandler(QObject *parent = 0);
    ~SkyExtDevDataHandler();

signals:
    void newExtDataAvailable(int slope, int inclLeftRight, int direction, int positionData);

public slots:
    void setOrientationData(int slope, int inclLeftRight);
    void setDirectionData(int direction);
    void setPositionData(int positionData);

private slots:
    void timerTimeout();

private:
    //members for stocking actual data
    int p_slope;
    int p_inclLefRight;
    int p_direction;
    int p_positionData;

    //members for stocking emited data
    int p_lSlope;
    int p_lInclLefRight;
    int p_lDirection;
    int p_lPositionData;

    QTimer* p_timer;


};

#endif // SKYEXTDEVDATAHANDLER_H
