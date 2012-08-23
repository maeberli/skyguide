#ifndef EXTERNALDEVICEIMPL_CMDMAGNETOMETER_H
#define EXTERNALDEVICEIMPL_CMDMAGNETOMETER_H

#include "command.h"

namespace ExternalDeviceImpl {

class CmdMagnetometer : public Command
{
public:
    CmdMagnetometer(QString _data = "");
    QString prepareForSend() const;
    bool analyzeData();
    void decide(StarPointerCommunication& com);

    //Composante X (0-5 car.),Composante Y (0-5 car.),Composante Z (0-5 car.)	Les composantes sont des valeurs entre 0 et 65535.	$05,126,008,056*3E\r\n
private:
    int m_xComp;
    int m_yComp;
    int m_zComp;
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDMAGNETOMETER_H
