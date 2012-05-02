#ifndef EXTERNALDEVICEIMPL_CMDGUIDEMODE_H
#define EXTERNALDEVICEIMPL_CMDGUIDEMODE_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdGuideMode : public Command
{
public:
    CmdGuideMode(QString _data = "");
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDGUIDEMODE_H
