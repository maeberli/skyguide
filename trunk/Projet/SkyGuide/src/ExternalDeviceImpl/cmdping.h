#ifndef EXTERNALDEVICEIMPL_CMDPING_H
#define EXTERNALDEVICEIMPL_CMDPING_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdPing : public Command
{
public:
    CmdPing(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDPING_H
