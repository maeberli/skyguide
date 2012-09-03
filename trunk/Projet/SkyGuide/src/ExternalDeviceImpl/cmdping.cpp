/**
  * Class implementation file of CmdPing.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdping.h"

namespace ExternalDeviceImpl {

CmdPing::CmdPing(QString data)
    :Command(Command::Ping, data)
{
}

void CmdPing::decide(StarPointerCommunication &com)
{
    com.logVerbose(tr("received ping command."));
}

} // namespace ExternalDeviceImpl
