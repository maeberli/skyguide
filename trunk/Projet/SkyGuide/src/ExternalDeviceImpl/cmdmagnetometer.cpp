#include "cmdmagnetometer.h"

namespace ExternalDeviceImpl {

CmdMagnetometer::CmdMagnetometer(QString _data)
    :Command(Command::Magnetometer, _data)
{
}

} // namespace ExternalDeviceImpl
