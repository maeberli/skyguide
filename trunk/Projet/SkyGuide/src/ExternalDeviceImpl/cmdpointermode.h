#ifndef EXTERNALDEVICEIMPL_CMDPOINTERMODE_H
#define EXTERNALDEVICEIMPL_CMDPOINTERMODE_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdPointerMode : public Command
{
public:
    CmdPointerMode(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDPOINTERMODE_H
