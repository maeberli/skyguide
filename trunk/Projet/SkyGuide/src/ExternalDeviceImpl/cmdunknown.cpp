#include "cmdunknown.h"

namespace ExternalDeviceImpl {

CmdUnknwon::CmdUnknwon(QString _data)
    :Command(Command::Ping, _data)
{
}
} // namespace ExternalDeviceImpl
