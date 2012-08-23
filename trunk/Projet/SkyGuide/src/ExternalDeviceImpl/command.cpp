#include "command.h"

namespace ExternalDeviceImpl {

Command::Command(Commands _type, QString _data)
    : m_type(_type),
      m_data(_data)
{
}

bool Command::analyzeData()
{
    return true;
}

void Command::decide(StarPointerCommunication& com)
{
}

QString Command::prepareForSend() const
{
    return (this->m_type>9 ? QString("") : QString("0")) + QString::number(m_type) + QString(_SEP_);
}

} // namespace ExternalDeviceImpl
