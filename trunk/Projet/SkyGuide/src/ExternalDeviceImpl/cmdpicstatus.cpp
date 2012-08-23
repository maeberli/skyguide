#include "cmdpicstatus.h"

#include <QStringList>

namespace ExternalDeviceImpl {

CmdPicStatus::CmdPicStatus(QString _data)
    :Command(Command::Ping, _data)
{
}

bool CmdPicStatus::analyzeData()
{
    QStringList list = m_data.split(_SEP_);
    if(list.size() == 1)
    {
        m_status = list[0].toInt();

        return true;
    }

    return false;
}

QString CmdPicStatus::prepareForSend() const
{
    return (this->m_type>9 ? QString("") : QString("0")) + m_type + _SEP_
            + QString::number(m_status);
}

} // namespace ExternalDeviceImpl
