#ifndef EXTERNALDEVICEIMPL_CMDUNKNWON_H
#define EXTERNALDEVICEIMPL_CMDUNKNWON_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdUnknwon : public Command
{
public:
    CmdUnknwon(QString _data = "");
    void decide(StarPointerCommunication& com) {};
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDUNKNWON_H
