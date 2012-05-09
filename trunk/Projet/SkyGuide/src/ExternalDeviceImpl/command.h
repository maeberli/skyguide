#ifndef EXTERNALDEVICEIMPL_COMMAND_H
#define EXTERNALDEVICEIMPL_COMMAND_H

#include <QString>

namespace ExternalDeviceImpl {

class Command
{

public:
    enum Commands {
        Ping            = 00,
        GuideMode       = 01,
        PointerMode     = 02,
        GPS             = 03,
        Accelerometer   = 04,
        Magnetometer    = 05,
        PICStatus       = 06
    };

    Command(Commands _type, QString _data);

private:
    Commands m_type;
    QString m_data;

    virtual void analyizeData()=0;
    
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_COMMAND_H
