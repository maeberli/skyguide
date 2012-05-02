#include "cmdpicstatus.h"

namespace ExternalDeviceImpl {

CmdPicStatus::CmdPicStatus(QString _data)
    :Command(Command::Ping, _data)
{
}

} // namespace ExternalDeviceImpl
