#include "cmdguidemode.h"

#include <QStringList>
#include <QTextStream>

namespace ExternalDeviceImpl {

CmdGuideMode::CmdGuideMode(QString _data)
    :Command(Command::GuideMode, _data),
      m_flashDirection(0)
{
}

CmdGuideMode::CmdGuideMode(int flashDirection)
    :Command(Command::GuideMode, ""),
      m_flashDirection(flashDirection)
{
}

bool CmdGuideMode::analyzeData()
{
    QStringList list = m_data.split(_SEP_);
    if(list.size()==1)
    {
        this->m_flashDirection = list[0].toInt();

        return true;
    }

    return false;
}

QString CmdGuideMode::prepareForSend() const
{
    QString rv = "";
    QTextStream stream(&rv);
    stream.setRealNumberPrecision(4);
    stream.setRealNumberNotation(QTextStream::FixedNotation);
    stream << (this->m_type>9 ? QString("") : QString("0")) << m_type << _SEP_
           << m_flashDirection;

    return rv;

}

} // namespace ExternalDeviceImpl
