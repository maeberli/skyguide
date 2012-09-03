/**
  * Class implementation file of Command.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */

#include "command.h"

namespace ExternalDeviceImpl {

Command::Command(Commands type, QString data)
    : p_type(type),
      p_data(data)
{
}

bool Command::analyzeData()
{
    return true;
}

QString Command::prepareForSend() const
{
    return (this->p_type>9 ? QString("") : QString("0")) + QString::number(p_type) + QString(_SEP_);
}

} // namespace ExternalDeviceImpl
