#include "cmdguidemode.h"

#include <QStringList>

namespace ExternalDeviceImpl {

CmdGuideMode::CmdGuideMode(QString _data)
    :Command(Command::GuideMode, _data)
{
}

void CmdGuideMode::analyzeData()
{
    QStringList list = m_data.split(_SEP_);
    this->m_flashDirection = list[0].toInt();
}

QString CmdGuideMode::prepareForSend()
{
    return (this->m_type>9 ? QString("") : QString("0")) + m_type + _SEP_
            + QString::number(m_flashDirection);
}

} // namespace ExternalDeviceImpl
