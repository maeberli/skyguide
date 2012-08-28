#include "cmdgps.h"

#include <QStringList>
#include <QTextStream>

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

CmdGPS::CmdGPS(QString _data)
    :Command(Command::GPS, _data)
{
}

bool CmdGPS::analyzeData()
{

    QRegExp reg("^[0-9]{4}\\.[0-9]{4},[NS],[0-9]{5}\\.[0-9]{4},[EW]$");
    if(reg.indexIn(m_data) == 0)
    {
        QStringList list = m_data.split(_SEP_);
        QString lat = list[0];
        char latSide = list[1].at(0).toAscii();
        QString longi = list[2];
        char longiSide = list[3].at(0).toAscii();

        m_latitude = lat.left(2).toInt() + lat.right(7).toDouble()/60;
        m_latitude = (latSide == 'N' ? m_latitude : -m_latitude);

        m_longitude = longi.left(3).toInt() + longi.right(7).toDouble()/60;
        m_longitude = (longiSide == 'E' ? m_longitude : -m_longitude);


        return true;
    }
    return false;
}

QString CmdGPS::prepareForSend() const
{
    double lati = (m_latitude < 0 ? m_latitude * (-1) : m_latitude);
    double longi = (m_longitude < 0 ? m_longitude * (-1) : m_longitude);

    int latiDeg = (int)lati;
    double latiMin = (lati - latiDeg) * 60;

    int longiDeg = (int)longi;
    double longiMin = (longi - longiDeg) * 60;

    QString rv = "";
    QTextStream stream(&rv);
    stream.setRealNumberPrecision(4);
    stream.setRealNumberNotation(QTextStream::FixedNotation);
    stream << (this->m_type>9 ? QString("") : QString("0")) << m_type << _SEP_
           << latiDeg << latiMin << _SEP_
           << ( m_latitude < 0 ? "S" : "N" ) << _SEP_
           << longiDeg << longiMin << _SEP_
           << ( m_longitude < 0 ? "W" : "E" );

    return rv;

}

void CmdGPS::decide(StarPointerCommunication& com)
{
    emit com.receivedGPSData(this->m_longitude, this->m_latitude);
}

} // namespace ExternalDeviceImpl
