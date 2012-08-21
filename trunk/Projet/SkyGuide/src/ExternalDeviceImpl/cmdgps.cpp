#include "cmdgps.h"

#include <QStringList>

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

CmdGPS::CmdGPS(QString _data)
    :Command(Command::GPS, _data)
{
}

void CmdGPS::analyzeData()
{
    QStringList list = m_data.split(",");
    m_latitude = list[0];
    m_latitudeSide = list[1].at(0).toAscii();
    m_longitude = list[2];
    m_longitudeSide = list[3].at(0).toAscii();
}

QString CmdGPS::prepareForSend()
{
    return (this->m_type>9 ? QString("") : QString("0")) + m_type + ","
            + m_latitude + ","
            + m_latitudeSide + ","
            + m_longitude + ","
            + m_longitudeSide + ",";

}

void CmdGPS::decide(StarPointerCommunication& com)
{
    emit com.receivedGPSData(this->m_latitude, this->m_latitudeSide, this->m_longitude, this->m_longitudeSide);
}

} // namespace ExternalDeviceImpl
