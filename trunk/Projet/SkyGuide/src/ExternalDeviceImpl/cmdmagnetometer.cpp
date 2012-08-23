#include "cmdmagnetometer.h"

#include <QStringList>

#include "starpointercommunication.h"

#define NULLPOINT_OFFSET 32768

namespace ExternalDeviceImpl {

CmdMagnetometer::CmdMagnetometer(QString _data)
    :Command(Command::Magnetometer, _data)
{
}


bool CmdMagnetometer::analyzeData()
{
    QStringList list = m_data.split(_SEP_);
    if(list.size() == 3)
    {
        m_xComp = list[0].toInt() - NULLPOINT_OFFSET;
        m_yComp = list[1].toInt() - NULLPOINT_OFFSET;
        m_zComp = list[2].toInt() - NULLPOINT_OFFSET;

        return true;
    }

    return false;
}

QString CmdMagnetometer::prepareForSend() const
{
    return (this->m_type>9 ? QString("") : QString("0")) + m_type + _SEP_
            + m_xComp + _SEP_
            + QString::number(m_xComp + NULLPOINT_OFFSET) + _SEP_
            + QString::number(m_yComp + NULLPOINT_OFFSET) + _SEP_
            + QString::number(m_zComp + NULLPOINT_OFFSET);
}

void CmdMagnetometer::decide(StarPointerCommunication& com)
{
    emit com.receivedMagnetometerData(m_xComp, m_yComp, m_zComp);
}
} // namespace ExternalDeviceImpl
