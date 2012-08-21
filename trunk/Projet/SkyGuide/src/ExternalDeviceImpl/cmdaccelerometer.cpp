#include "cmdaccelerometer.h"

#include <QStringList>

#include "starpointercommunication.h"

#define NULLPOINT_OFFSET 32768

namespace ExternalDeviceImpl {

CmdAccelerometer::CmdAccelerometer(QString _data)
    :Command(Command::Accelerometer, _data)
{
}


void CmdAccelerometer::analyzeData()
{
    QStringList list = m_data.split(_SEP_);
    m_xComp = list[0].toInt() - NULLPOINT_OFFSET;
    m_yComp = list[1].toInt() - NULLPOINT_OFFSET;
    m_zComp = list[2].toInt() - NULLPOINT_OFFSET;
}

QString CmdAccelerometer::prepareForSend()
{
    return (this->m_type>9 ? QString("") : QString("0")) + m_type + _SEP_
            + QString::number(m_xComp + NULLPOINT_OFFSET) + _SEP_
            + QString::number(m_yComp + NULLPOINT_OFFSET) + _SEP_
            + QString::number(m_zComp + NULLPOINT_OFFSET);
}

void CmdAccelerometer::decide(StarPointerCommunication& com)
{
    emit com.receivedAccelormeterData(m_xComp, m_yComp, m_zComp);
}

} // namespace ExternalDeviceImpl
