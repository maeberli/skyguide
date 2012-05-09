#ifndef EXTERNALDEVICEIMPL_CMDACCELEROMETER_H
#define EXTERNALDEVICEIMPL_CMDACCELEROMETER_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdAccelerometer : public Command
{
public:
    CmdAccelerometer(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDACCELEROMETER_H
