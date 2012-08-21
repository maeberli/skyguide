#ifndef EXTERNALDEVICEIMPL_CMDGUIDEMODE_H
#define EXTERNALDEVICEIMPL_CMDGUIDEMODE_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdGuideMode : public Command
{
public:
    CmdGuideMode(QString _data = "");
    virtual QString prepareForSend();
    virtual void analyzeData();
    void decide(StarPointerCommunication& com) {};

private:
    int m_flashDirection;
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDGUIDEMODE_H
