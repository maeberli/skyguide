/**
  * Class implementation file of CmdGps.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdgps.h"

#include <QStringList>
#include <QTextStream>

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

CmdGPS::CmdGPS(QString data)
    :Command(Command::GPS, data)
{
}

bool CmdGPS::analyzeData()
{

    QRegExp reg("^[0-9]{4}\\.[0-9]{4},[NS],[0-9]{5}\\.[0-9]{4},[EW]$");
    if(reg.indexIn(p_data) == 0)
    {
        QStringList list = p_data.split(_SEP_);
        QString lat = list[0];
        char latSide = list[1].at(0).toAscii();
        QString longi = list[2];
        char longiSide = list[3].at(0).toAscii();

        p_latitude = lat.left(2).toInt() + lat.right(7).toDouble()/60;
        p_latitude = (latSide == 'N' ? p_latitude : -p_latitude);

        p_longitude = longi.left(3).toInt() + longi.right(7).toDouble()/60;
        p_longitude = (longiSide == 'E' ? p_longitude : -p_longitude);


        return true;
    }
    return false;
}

QString CmdGPS::prepareForSend() const
{
    double lati = (p_latitude < 0 ? p_latitude * (-1) : p_latitude);
    double longi = (p_longitude < 0 ? p_longitude * (-1) : p_longitude);

    int latiDeg = (int)lati;
    double latiMin = (lati - latiDeg) * 60;

    int longiDeg = (int)longi;
    double longiMin = (longi - longiDeg) * 60;

    QString rv = "";
    QTextStream stream(&rv);
    stream.setRealNumberPrecision(4);
    stream.setRealNumberNotation(QTextStream::FixedNotation);
    stream << (this->p_type>9 ? QString("") : QString("0")) << p_type << _SEP_
           << latiDeg << latiMin << _SEP_
           << ( p_latitude < 0 ? "S" : "N" ) << _SEP_
           << longiDeg << longiMin << _SEP_
           << ( p_longitude < 0 ? "W" : "E" );

    return rv;

}

void CmdGPS::decide(StarPointerCommunication& com)
{
    emit com.receivedGPSData(this->p_longitude, this->p_latitude);
}

} // namespace ExternalDeviceImpl
