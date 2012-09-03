/**
  * Class implementation file of CmdMagnetometer.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdmagnetometer.h"

#include <QStringList>

#include "starpointercommunication.h"

#define NULLPOINT_OFFSET 32768

namespace ExternalDeviceImpl {

CmdMagnetometer::CmdMagnetometer(QString data)
    :Command(Command::Magnetometer, data)
{
}


bool CmdMagnetometer::analyzeData()
{
    QStringList list = p_data.split(_SEP_);
    if(list.size() == 3)
    {
        p_xComp = list[0].toInt() - NULLPOINT_OFFSET;
        p_yComp = list[1].toInt() - NULLPOINT_OFFSET;
        p_zComp = list[2].toInt() - NULLPOINT_OFFSET;

        return true;
    }

    return false;
}

QString CmdMagnetometer::prepareForSend() const
{
    return (this->p_type>9 ? QString("") : QString("0")) + p_type + _SEP_
            + p_xComp + _SEP_
            + QString::number(p_xComp + NULLPOINT_OFFSET) + _SEP_
            + QString::number(p_yComp + NULLPOINT_OFFSET) + _SEP_
            + QString::number(p_zComp + NULLPOINT_OFFSET);
}

void CmdMagnetometer::decide(StarPointerCommunication& com)
{
    emit com.receivedMagnetometerData(p_xComp, p_yComp, p_zComp);
}
} // namespace ExternalDeviceImpl
