/**
  * Class implementation file of CmdPointerMode.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "cmdpointermode.h"

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

CmdPointerMode::CmdPointerMode(QString data)
    :Command(Command::PointerMode, data)
{
}

void CmdPointerMode::decide(StarPointerCommunication &com)
{
    com.logVerbose(tr("Received PointerMode command."));
}
} // namespace ExternalDeviceImpl
