#include "cmdping.h"

namespace ExternalDeviceImpl {

CmdPing::CmdPing(QString _data)
    :Command(Command::Ping, _data)
{
}

void CmdPing::decide(StarPointerCommunication& com)
{
}

} // namespace ExternalDeviceImpl
