#include "command.h"

namespace ExternalDeviceImpl {

Command::Command(Commands _type, QString _data)
    : m_type(_type),
      m_data(_data)
{
}

} // namespace ExternalDeviceImpl
