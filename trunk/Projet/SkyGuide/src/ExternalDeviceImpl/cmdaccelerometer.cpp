#include "cmdaccelerometer.h"

namespace ExternalDeviceImpl {

CmdAccelerometer::CmdAccelerometer(QString _data)
    :Command(Command::Accelerometer, _data)
{
}

} // namespace ExternalDeviceImpl
