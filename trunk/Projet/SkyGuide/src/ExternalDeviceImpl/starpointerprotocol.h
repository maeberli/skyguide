#ifndef STARPOINTERPROTOCOL_H
#define STARPOINTERPROTOCOL_H

#include <QObject>
#include "abstractserial.h"
#include "command.h"

namespace ExternalDeviceImpl {

class StarPointerCommunication : public QObject
{
    Q_OBJECT
public:
    explicit StarPointerCommunication(QObject *parent = 0);
    ~StarPointerCommunication();

private slots:
        void incommingData();

private:
    AbstractSerial *m_conn;

    static void checkCRC();
    static Command* getCommandObject();
};

} // namespace ExternalDeviceImpl

#endif // STARPOINTERPROTOCOL_H
