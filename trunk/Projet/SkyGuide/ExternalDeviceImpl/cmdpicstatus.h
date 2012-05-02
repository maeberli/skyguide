#ifndef EXTERNALDEVICEIMPL_CMDPICSTATUS_H
#define EXTERNALDEVICEIMPL_CMDPICSTATUS_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdPicStatus : public Command
{
public:
    CmdPicStatus(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDPICSTATUS_H
