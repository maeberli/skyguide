/**
  * Class implementation file of CmdGuideMode.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdguidemode.h"

#include <QStringList>
#include <QTextStream>

namespace ExternalDeviceImpl {

CmdGuideMode::CmdGuideMode(QString data)
    :Command(Command::GuideMode, data),
      p_flashDirection(0)
{
}

CmdGuideMode::CmdGuideMode(int flashDirection)
    :Command(Command::GuideMode, ""),
      p_flashDirection(flashDirection)
{
}

bool CmdGuideMode::analyzeData()
{
    QStringList list = p_data.split(_SEP_);
    if(list.size()==1)
    {
        this->p_flashDirection = list[0].toInt();

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
    stream << (this->p_type>9 ? QString("") : QString("0")) << p_type << _SEP_
           << p_flashDirection;

    return rv;
}

void CmdGuideMode::decide(StarPointerCommunication &com)
{
    com.logVerbose(tr("Received GuideMode commmand."));
}

} // namespace ExternalDeviceImpl
