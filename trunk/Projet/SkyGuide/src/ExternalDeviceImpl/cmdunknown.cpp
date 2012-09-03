/**
  * Class implementation file of CmdUnknwon.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdunknown.h"

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

CmdUnknwon::CmdUnknwon(QString data)
    :Command(Command::Ping, data)
{
}

void CmdUnknwon::decide(StarPointerCommunication &com)
{
    com.logInfo(tr("Unknown command received"));
}

} // namespace ExternalDeviceImpl
