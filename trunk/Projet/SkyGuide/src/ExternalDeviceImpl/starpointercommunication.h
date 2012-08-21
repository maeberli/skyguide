#ifndef STARPOINTERCOMMUNICATION_H
#define STARPOINTERCOMMUNICATION_H

#include <QObject>
#include <QTimer>
#include "abstractserial.h"

namespace ExternalDeviceImpl {

#define PING_INTERVAL 2999

class Command;

class StarPointerCommunication : public QObject
{
    Q_OBJECT
public:
    enum ProtocollStates {
        ModeGuide           = 00,
        ModePointer         = 01
    };

    explicit StarPointerCommunication(QObject *parent = 0);
    ~StarPointerCommunication();

signals:
    void receivedGPSData(QString longitude, char logSide,QString lat,char latSide);
    void receivedAccelormeterData(int xComp, int yComp, int zComp);
    void receivedMagnetometerData(int xComp, int yComp, int zComp);


private slots:
        void incommingData();
        void signalStatusChanged(const QString &status, QDateTime current);
        bool initConnection();

private:
    AbstractSerial *m_conn;
    ProtocollStates m_actState;
    QTimer *m_pingTimer;

    bool send(Command* cmd);

    bool checkCRC(QString data);
    QString calculateCRC(const QString& data);
    Command* getCommandObject(QString data);

    friend class CmdGPS;
    friend class CmdAccelerometer;
    friend class CmdMagnetometer;
};

} // namespace ExternalDeviceImpl

#endif // STARPOINTERCOMMUNICATION_H
