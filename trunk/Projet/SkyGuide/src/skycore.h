#ifndef SKYCORE_H
#define SKYCORE_H

#include <QObject>
#include <QList>

#include <skycomponent.h>
#include <skydatabase.h>
#include <skylogger.h>
#include <skycalculator.h>
#include <skyexternaldevice.h>
#include <skygui.h>


#include <math.h>
struct Vect3D
{
    double x;
    double y;
    double z;
};

class SkyCore : SkyComponent
{
    Q_OBJECT
public:
    explicit SkyCore(QObject *parent = 0);
    ~SkyCore();

    void startGui();

public slots:
    virtual void start();
    virtual void stop();

private slots:
    void calculateRange(QString longitude, char longSide, QString latitude, char latSide,
                        int accXComp, int accYComp, int accZComp,
                        int magXComp, int magYComp, int magZComp);


private:
    SKYLOGGER::SkyLogger* p_logger;
    SkyConfiguration* p_config;
    SkyDatabase* p_database;
    SkyCalculator* p_calculator;
    SkyExternalDevice* p_externalDevice;
    SkyGui* p_gui;
    QList<SkyElement* >* allStars;
    QList<SkyGuiElement* >* guiList;

    static Vect3D crossProduct(const Vect3D& v1, const Vect3D& v2)
    {
        Vect3D rv;
        rv.x =  v1.y*v2.z - v1.z*v2.y;
        rv.y =  v1.z*v2.x - v1.x*v2.z;
        rv.z =  v1.x*v2.y - v1.y*v2.x;
        return rv;
    }

    static double scalarProduct(const Vect3D& v1, const Vect3D& v2)
    {
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    static double getNorm(const Vect3D& v)
    {
        return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }

    static Vect3D getUnitVector(const Vect3D& v)
    {
        Vect3D rv;
        double norm = getNorm(v);

        rv.x = v.x / norm;
        rv.y = v.y / norm;
        rv.z = v.z / norm;

        return rv;
    }

};

#endif // SKYCORE_H
