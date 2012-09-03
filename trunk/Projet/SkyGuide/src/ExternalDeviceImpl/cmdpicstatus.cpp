/**
  * Class implementation file of CmdPicStatus.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdpicstatus.h"

#include <QStringList>

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

CmdPicStatus::CmdPicStatus(QString data)
    :Command(Command::Ping, data)
{
}

bool CmdPicStatus::analyzeData()
{
    QStringList list = p_data.split(_SEP_);
    if(list.size() == 1)
    {
        p_status = list[0].toInt();

        return true;
    }

    return false;
}

QString CmdPicStatus::prepareForSend() const
{
    return (this->p_type>9 ? QString("") : QString("0")) + p_type + _SEP_
            + QString::number(p_status);
}

void CmdPicStatus::decide(StarPointerCommunication &com)
{
    com.logInfo(tr("PicStatus received. Code: %1").arg(p_status));
}

} // namespace ExternalDeviceImpl
