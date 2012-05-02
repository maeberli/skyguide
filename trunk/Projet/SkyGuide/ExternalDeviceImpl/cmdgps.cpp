#include "cmdgps.h"

namespace ExternalDeviceImpl {

CmdGPS::CmdGPS(QString _data)
    :Command(Command::GPS, _data)
{
}

} // namespace ExternalDeviceImpl
