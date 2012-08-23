#ifndef EXTERNALDEVICEIMPL_CMDPICSTATUS_H
#define EXTERNALDEVICEIMPL_CMDPICSTATUS_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdPicStatus : public Command
{
public:
    CmdPicStatus(QString _data = "");
    QString prepareForSend() const;
    bool analyzeData();
    void decide(StarPointerCommunication& com) {};

private:
    int m_status;
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDPICSTATUS_H
