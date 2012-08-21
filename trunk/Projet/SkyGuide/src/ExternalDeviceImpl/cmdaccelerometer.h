#ifndef EXTERNALDEVICEIMPL_CMDACCELEROMETER_H
#define EXTERNALDEVICEIMPL_CMDACCELEROMETER_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdAccelerometer : public Command
{
public:
    CmdAccelerometer(QString _data = "");
    virtual QString prepareForSend();
    void analyzeData();
    void decide(StarPointerCommunication& com);

private:
    int m_xComp;
    int m_yComp;
    int m_zComp;
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDACCELEROMETER_H
