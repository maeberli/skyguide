#ifndef EXTERNALDEVICEIMPL_CMDGPS_H
#define EXTERNALDEVICEIMPL_CMDGPS_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdGPS : public Command
{
public:
    CmdGPS(QString _data = "");
    virtual QString prepareForSend();
    void analyzeData();
    void decide(StarPointerCommunication& com);

private:
    QString m_longitude;
    char m_longitudeSide;
    QString m_latitude;
    char m_latitudeSide;

};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDGPS_H
