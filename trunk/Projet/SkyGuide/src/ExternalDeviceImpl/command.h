#ifndef EXTERNALDEVICEIMPL_COMMAND_H
#define EXTERNALDEVICEIMPL_COMMAND_H

#include <QString>

namespace ExternalDeviceImpl {

class StarPointerCommunication;

#define _SEP_ ','

class Command
{

public:
    enum Commands {
        Ping            = 00,
        PointerMode     = 01,
        GuideMode       = 02,
        GPS             = 03,
        Accelerometer   = 04,
        Magnetometer    = 05,
        PICStatus       = 06
    };

    Command(Commands _type, QString _data);

    virtual QString prepareForSend() const;
    virtual bool analyzeData();
    virtual void decide(StarPointerCommunication& com) = 0;

protected:
    Commands m_type;
    QString m_data;
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_COMMAND_H
