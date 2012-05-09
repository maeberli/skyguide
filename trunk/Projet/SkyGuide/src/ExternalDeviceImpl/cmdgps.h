#ifndef EXTERNALDEVICEIMPL_CMDGPS_H
#define EXTERNALDEVICEIMPL_CMDGPS_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdGPS : public Command
{
public:
    CmdGPS(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDGPS_H
