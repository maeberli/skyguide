#ifndef EXTERNALDEVICEIMPL_CMDMAGNETOMETER_H
#define EXTERNALDEVICEIMPL_CMDMAGNETOMETER_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdMagnetometer : public Command
{
public:
    CmdMagnetometer(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDMAGNETOMETER_H
