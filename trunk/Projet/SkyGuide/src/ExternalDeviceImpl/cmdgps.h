#ifndef EXTERNALDEVICEIMPL_CMDGPS_H
#define EXTERNALDEVICEIMPL_CMDGPS_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdGPS : public Command
{
public:
    CmdGPS(QString _data = "");
    QString prepareForSend() const;
    bool analyzeData();
    void decide(StarPointerCommunication& com);

private:
    double m_longitude;
    double m_latitude;

};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDGPS_H
